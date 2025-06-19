/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:36:58 by root              #+#    #+#             */
/*   Updated: 2025/06/19 14:09:37 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			close(pipefd[0]);
			close(pipefd[1]);
			restore_default_signals();
			return (-2); // Signal reçu, on interrompt
		}
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

int	apply_redirections(t_redir *redirs)
{
	int		fd;
	t_redir	*curr = redirs;

	while (curr)
	{
		if (curr->type == TOKEN_REDIR_IN)
		{
			fd = open(curr->file, O_RDONLY);
			if (fd < 0)
				return (perror(curr->file), -1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (curr->type == TOKEN_REDIR_OUT)
		{
			fd = open(curr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror(curr->file), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (curr->type == TOKEN_REDIR_APPEND)
		{
			fd = open(curr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(curr->file), -1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (curr->type == TOKEN_HEREDOC)
		{
			fd = create_heredoc_pipe(curr->file);
			if (fd == -2)
				return (EXIT_SIGINT);
			if (fd < 0)
				return (perror("heredoc"), -1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		curr = curr->next;
	}
	return (0);
}
