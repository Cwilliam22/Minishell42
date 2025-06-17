/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:59:42 by root              #+#    #+#             */
/*   Updated: 2025/06/17 12:46:11 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* État actuel du shell pour adapter le comportement des signaux */
static int	g_signal_state = SIGNAL_INTERACTIVE;

/**
 * Handler pour SIGINT (ctrl-C)
 * Comportement adapté selon le contexte du shell
 */
static void	handle_sigint(int sig)
{
	g_signal_received = sig;
	
	if (g_signal_state == SIGNAL_INTERACTIVE)
	{
		/* Mode interactif : nouveau prompt sur nouvelle ligne */
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_signal_state == SIGNAL_HEREDOC)
	{
		/* Mode heredoc : interrompre la lecture */
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	/* Mode execution : le signal sera géré par le processus parent */
}

/**
 * Handler pour SIGQUIT (ctrl-\)
 * En mode interactif : ignore le signal
 * En mode execution : laisse le comportement par défaut
 */
static void	handle_sigquit(int sig)
{
	if (g_signal_state == SIGNAL_INTERACTIVE || g_signal_state == SIGNAL_HEREDOC)
	{
		/* Mode interactif/heredoc : ignorer le signal */
		g_signal_received = 0;
	}
	else
	{
		/* Mode execution : comportement par défaut (core dump) */
		g_signal_received = sig;
	}
}

/**
 * Configuration des signaux pour le mode interactif
 */
void	setup_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	/* Configuration SIGINT */
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	/* Configuration SIGQUIT */
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = handle_sigquit;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/**
 * Configuration des signaux pour le mode execution
 */
static void	setup_execution_signals(void)
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
 * Restaurer les signaux par défaut (pour les processus enfants)
 */
void	restore_default_signals(void)
{
	struct sigaction	sa_default;

	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_handler = SIG_DFL;
	sa_default.sa_flags = 0;

	sigaction(SIGINT, &sa_default, NULL);
	sigaction(SIGQUIT, &sa_default, NULL);
}

/**
 * Configuration initiale des signaux
 * À appeler au démarrage du shell
 */
void	setup_signals(void)
{
	g_signal_received = 0;
	g_signal_state = SIGNAL_INTERACTIVE;
	setup_interactive_signals();
}

/**
 * Changer l'état du shell pour adapter le comportement des signaux
 * @param state: Nouvel état (SIGNAL_INTERACTIVE, SIGNAL_EXECUTING, SIGNAL_HEREDOC)
 */
void	set_signal_state(int state)
{
	g_signal_state = state;
	
	if (state == SIGNAL_INTERACTIVE || state == SIGNAL_HEREDOC)
	{
		setup_interactive_signals();
	}
	else if (state == SIGNAL_EXECUTING)
	{
		setup_execution_signals();
	}
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
	exit_code = 0;
	
	if (signal_num == SIGINT)
	{
		exit_code = 130;
	}
	else if (signal_num == SIGQUIT)
	{
		exit_code = 131;
	}
	
	/* Reset signal */
	g_signal_received = 0;
	
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
 * Configuration spéciale pour heredoc
 * Permet d'interrompre proprement la lecture
 */
void	setup_heredoc_signals(void)
{
	set_signal_state(SIGNAL_HEREDOC);
}

/**
 * Configuration pour l'exécution de commandes
 * Les signaux sont ignorés dans le parent, traités dans l'enfant
 */
void	setup_exec_signals(void)
{
	set_signal_state(SIGNAL_EXECUTING);
}

/**
 * Retour au mode interactif
 */
void	setup_interactive_mode(void)
{
	set_signal_state(SIGNAL_INTERACTIVE);
}

/**
 * Gestionnaire spécial pour les processus enfants
 * Restaure le comportement par défaut des signaux
 */
void	setup_child_signals(void)
{
	restore_default_signals();
}

/**
 * Attendre la fin d'un processus enfant en gérant les signaux
 * @param pid: PID du processus à attendre
 * @return: Code de sortie du processus
 */
int	wait_child_with_signals(pid_t pid)
{
	int		status;
	int		exit_code;
	pid_t	result;

	exit_code = 0;
	
	while (1)
	{
		result = waitpid(pid, &status, 0);
		
		if (result == -1)
		{
			if (errno == EINTR)
			{
				/* Interrompu par un signal, continuer */
				continue;
			}
			/* Erreur réelle */
			perror("waitpid");
			return (1);
		}
		
		/* Processus terminé */
		break;
	}
	
	/* Analyser le code de sortie */
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
	
	return (exit_code);
}

/**
 * Fonction utilitaire pour debugging
 * Affiche l'état actuel des signaux
 */
void	debug_signal_state(void)
{
	const char	*state_names[] = {
		"UNKNOWN", "INTERACTIVE", "EXECUTING", "HEREDOC"
	};
	
	printf("DEBUG: Signal state: %s, Signal received: %d\n",
		state_names[g_signal_state], g_signal_received);
}
