/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:36:58 by root              #+#    #+#             */
/*   Updated: 2025/07/06 14:53:54 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Creates a pipe for heredoc input.
 * @brief This function sets up a pipe to read lines from the user until the
 * specified delimiter is entered.
 * It handles signals to allow for graceful termination on SIGINT.
 * @param delimiter The string that, when entered, will terminate the heredoc
 * input.
 * @return The read end of the pipe if successful, -1 on error, or -2 if SIGINT
 * is received.
 */
int	create_heredoc_pipe(const char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
		return (perror("pipe"), -1);
	setup_heredoc_signals();
	while (1)
	{
		if (g_signal_received == SIGINT)
			return (close(pipefd[0]), close(pipefd[1]),
				restore_default_signals(), -2);
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	restore_default_signals();
	return (pipefd[0]);
}

/**
 * Handles heredoc redirection by creating a pipe and reading input until the
 * specified delimiter is entered.
 * @param delimiter The string that, when entered, will terminate the heredoc
 * input.
 * @return 0 on success, EXIT_SIGINT if SIGINT is received, or 1 on error.
 */
static int	handle_heredoc(const char *delimiter)
{
	int	fd;

	fd = create_heredoc_pipe(delimiter);
	if (fd == -2)
		return (EXIT_SIGINT);
	if (fd < 0)
	{
		perror("heredoc");
		return (1);
	}
	if (dup_and_close(fd, STDIN_FILENO, "dup2"))
		return (1);
	return (0);
}

/**
 * Apply all redirections in the list
 * @param redirs: List of redirections to apply
 * @return: 0 on success, 1 on error
 */
int	apply_redirections(t_redir *redirs)
{
	t_redir	*curr;
	int		ret;

	curr = redirs;
	while (curr)
	{
		if (curr->type == TOKEN_REDIR_IN)
			ret = open_and_dup(curr->file, O_RDONLY, STDIN_FILENO);
		else if (curr->type == TOKEN_REDIR_OUT)
			ret = open_and_dup(curr->file, O_WRONLY | O_CREAT
					| O_TRUNC, STDOUT_FILENO);
		else if (curr->type == TOKEN_REDIR_APPEND)
			ret = open_and_dup(curr->file, O_WRONLY | O_CREAT
					| O_APPEND, STDOUT_FILENO);
		else if (curr->type == TOKEN_HEREDOC)
			ret = handle_heredoc(curr->file);
		else
			ret = 0;
		if (ret)
			return (ret);
		curr = curr->next;
	}
	return (0);
}
