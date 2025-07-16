/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:10:39 by root              #+#    #+#             */
/*   Updated: 2025/07/16 12:55:14 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_parent_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handler_sigint_execution(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	g_signal_received = SIGINT;
}

void	handler_sigquit_execution(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	g_signal_received = SIGQUIT;
}

void	sig_core_dump_parent_signal(void)
{
	signal(SIGINT, handler_sigint_execution);
	signal(SIGQUIT, handler_sigquit_execution);
}


