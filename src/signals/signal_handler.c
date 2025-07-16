/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:36:44 by alfavre           #+#    #+#             */
/*   Updated: 2025/07/16 12:53:11 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Signal handler for SIGINT (Ctrl+C) in interactive mode.
 * Sets the global variable, prints newline, clears readline input, and
 * refreshes prompt.
 * @param sig The signal number received (should be SIGINT).
 */
void	handle_sigint(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal_received = sig;
}

void	handler_sigquit(int sig)
{
	(void)sig;
	ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	g_signal_received = SIGQUIT;
}

void	handle_signal(t_shell *shell)
{
	if (g_signal_received == SIGINT)
		exit_codes(shell, 130, NULL);
	g_signal_received = 0;
}

void	wait_for_all(t_shell *shell, pid_t last_pid)
{
	int		status;
	int		exit_status;
	pid_t	pid;
	int		sig;

	exit_status = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGINT)
				{
					//write(STDERR_FILENO, "\n", 1);
					exit_status = 130;
				}
				else if (sig == SIGQUIT)
				{
					write(STDERR_FILENO, "Quit (core dumped)\n", 19);
					exit_status = 131;
				}
				else
					exit_status = 128 + sig;
			}
			else
				exit_status = EXIT_FAILURE;
		}
	}
	exit_codes(shell, exit_status, NULL);
}
