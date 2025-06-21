/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:36:58 by root              #+#    #+#             */
/*   Updated: 2025/06/21 12:18:32 by root             ###   ########.fr       */
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

static int	open_and_dup(const char *file, int flags, int stdfd)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
		return (perror(file), 1);
	if (dup2(fd, stdfd) < 0)
	{
		close(fd);
		return (perror("dup2"), 1);
	}
	close(fd);
	return (0);
}

static int	dup_and_close(int fd, int stdfd, const char *err)
{
	if (dup2(fd, stdfd) < 0)
	{
		close(fd);
		perror(err);
		return (1);
	}
	close(fd);
	return (0);
}

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

int	apply_redirections(t_redir *redirs)
{
	t_redir	*curr;
	int		ret;

	curr = redirs;
	while (curr)
	{
		if (curr->type == TOKEN_REDIR_IN)
		{
			if (open_and_dup(curr->file, O_RDONLY, STDIN_FILENO))
				return (1);
		}
		else if (curr->type == TOKEN_REDIR_OUT)
		{
			if (open_and_dup(curr->file, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO))
				return (1);
		}
		else if (curr->type == TOKEN_REDIR_APPEND)
		{
			if (open_and_dup(curr->file, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO))
				return (1);
		}
		else if (curr->type == TOKEN_HEREDOC)
		{
			ret = handle_heredoc(curr->file);
			if (ret)
				return (ret);
		}
		curr = curr->next;
	}
	return (0);
}
