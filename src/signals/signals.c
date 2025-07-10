/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:10:39 by root              #+#    #+#             */
/*   Updated: 2025/07/10 02:19:45 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Variable globale unique qui encode TOUT l'état des signaux */
int	g_signal_received = 0;

static void	handle_sigint_heredoc(int sig);

/**
 * Handler pour SIGINT (ctrl-C) - Version corrigée
 * Comportement adapté selon le contexte, mais sans variable d'état globale
 */
static void	handle_sigint(int sig)
{
	g_signal_received = sig;  /* Stocker seulement le numéro du signal */
	
	/* Comportement par défaut pour mode interactif */
	/* On suppose qu'on est en mode interactif si on reçoit le signal */
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * Handler spécialisé pour heredoc (sans rl_redisplay)
 */
static void	handle_sigint_heredoc(int sig)
{
	g_signal_received = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	/* Pas de rl_redisplay() pour heredoc */
}

/**
 * Configuration des signaux pour le mode interactif
 */
void	setup_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	/* Reset signal flag */
	g_signal_received = 0;

	/* Configuration SIGINT */
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	/* Configuration SIGQUIT - ignoré en mode interactif */
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/**
 * Configuration des signaux pour le mode execution
 */
void	setup_execution_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	/* SIGINT : ignorer dans le processus parent */
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = SIG_IGN;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	/* SIGQUIT : ignorer dans le processus parent */
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/**
 * Configuration des signaux pour heredoc
 * Même handler que interactif mais sans redisplay
 */
void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int;

	g_signal_received = 0;

	/* SIGINT avec handler spécial pour heredoc */
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = handle_sigint_heredoc;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	/* SIGQUIT ignoré */
	signal(SIGQUIT, SIG_IGN);
}

/**
 * Restaurer les signaux par défaut (pour processus enfants)
 */
void	restore_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * Vérifier si un signal a été reçu et retourner son code de sortie
 * @return: Code de sortie approprié (130 pour SIGINT, 131 pour SIGQUIT, 0 sinon)
 */
int	check_and_handle_signal(void)
{
	int	signal_num;
	int	exit_code;

	signal_num = g_signal_received;
	g_signal_received = 0;
	if (signal_num == SIGINT)
		exit_code = 130;
	else if (signal_num == SIGQUIT)
		exit_code = 131;
	else
		exit_code = 0;
	return (exit_code);
}

/**
 * Vérifier simplement si un signal a été reçu
 * @return: 1 si signal reçu, 0 sinon
 */
int	signal_received(void)
{
	return (g_signal_received != 0);
}

/**
 * Reset la variable globale de signal
 */
void	reset_signal(void)
{
	g_signal_received = 0;
}

/**
 * Obtenir le numéro du signal reçu
 * @return: Numéro du signal ou 0 si aucun
 */
int	get_signal_number(void)
{
	return (g_signal_received);
}

/**
 * Configuration initiale des signaux
 */
void	setup_signals(void)
{
	signal(SIGPIPE, SIG_IGN);
	g_signal_received = 0;
	setup_interactive_signals();
}

/**
 * Attendre un processus enfant en gérant les signaux
 * @param pid: PID du processus à attendre
 * @return: Code de sortie du processus
 */
int	wait_child_with_signals(pid_t pid)
{
	int		status;
	int		exit_code;
	pid_t	result;

	exit_code = 0;
	
	/* Configurer pour mode exécution */
	setup_execution_signals();
	
	/* Attendre le processus enfant */
	while (1)
	{
		result = waitpid(pid, &status, 0);
		
		if (result == -1)
		{
			if (errno == EINTR)
				continue;
			perror("waitpid");
			exit_code = 1;
			break;
		}
		
		/* Processus terminé */
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			
			if (sig == SIGINT)
			{
				exit_code = 130;
				write(STDOUT_FILENO, "\n", 1);
			}
			else if (sig == SIGQUIT)
			{
				exit_code = 131;
				write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
			}
			else
			{
				exit_code = 128 + sig;
			}
		}
		
		break;
	}
	
	/* Retour au mode interactif */
	setup_interactive_signals();
	
	return (exit_code);
}