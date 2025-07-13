/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:36:44 by alfavre           #+#    #+#             */
/*   Updated: 2025/07/13 16:04:42 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Signal handler for SIGINT (Ctrl+C) in interactive mode.
 * Sets the global variable, prints newline, clears readline input, and
 * refreshes prompt.
 * @param sig The signal number received (should be SIGINT).
 */
void handle_sigint(int sig)
{
	g_signal_received = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * Signal handler for SIGINT (Ctrl+C) during heredoc input.
 * Same as interactive but without prompt redisplay.
 * @param sig The signal number received (should be SIGINT).
 */
void	handle_sigint_heredoc(int sig)
{
	g_signal_received = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}
