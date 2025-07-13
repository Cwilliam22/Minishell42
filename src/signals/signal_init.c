/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:10:39 by root              #+#    #+#             */
/*   Updated: 2025/07/13 13:38:22 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Configuration initiale des signaux
 * Ignore SIGPIPE et configure les signaux interactifs
 */
void	setup_signals(void)
{
	signal(SIGPIPE, SIG_IGN);
	g_signal_received = 0;
	setup_interactive_signals();
}

/**
 * Gérer le statut d'un processus terminé par un signal
 * @param sig: Numéro du signal qui a terminé le processus
 * @return: Code de sortie approprié
 */
static int	handle_signal_termination(int sig)
{
	int	exit_code;

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
		exit_code = 128 + sig;
	return (exit_code);
}

/**
 * Traiter le statut de sortie d'un processus enfant
 * @param status: Statut retourné par waitpid
 * @return: Code de sortie du processus
 */
static int	process_child_status(int status)
{
	int	exit_code;
	int	sig;

	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		exit_code = handle_signal_termination(sig);
	}
	else
		exit_code = 0;
	return (exit_code);
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
	setup_execution_signals();
	while (1)
	{
		result = waitpid(pid, &status, 0);
		if (result == -1)
		{
			if (errno == EINTR)
				continue ;
			perror("waitpid");
			exit_code = 1;
			break ;
		}
		exit_code = process_child_status(status);
		break ;
	}
	setup_interactive_signals();
	return (exit_code);
}
