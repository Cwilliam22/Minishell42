/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:34:49 by alexis            #+#    #+#             */
/*   Updated: 2025/07/16 12:49:43 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handler_sigint_child(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	g_signal_received = SIGINT;
}

void	handler_sigint_heredoc_child(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	heredoc_child_signal(void)
{
	signal(SIGINT, handler_sigint_heredoc_child);
	signal(SIGQUIT, SIG_IGN);
}
