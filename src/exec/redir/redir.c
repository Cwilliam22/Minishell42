/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:36:58 by root              #+#    #+#             */
/*   Updated: 2025/07/16 12:17:37 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * Creates a pipe for heredoc input using fork for proper signal handling.
 * @param delimiter The string that, when entered, will terminate the heredoc
 * @param shell Shell structure for exit codes
 * @return The read end of the pipe if successful, -1 on error, or -2 if SIGINT
 */
int	create_heredoc_pipe(const char *delimiter, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	char	*line;

	if (pipe(pipefd) < 0)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == 0)
	{
		heredoc_child_signal();
		close(pipefd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break ;
			}
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		exit(0);
	}
	else if (pid > 0)
	{
		heredoc_parent_signal();
		close(pipefd[1]);
		wait(&status);
		parent_signal();
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			close(pipefd[0]);
			exit_codes(shell, 130, NULL);
			return (-2);
		}
		return (pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
		perror("fork");
		return (-1);
	}
}

/**
 * Handles heredoc redirection by creating a pipe and reading input until the
 * specified delimiter is entered.
 * @param delimiter The string that, when entered, will terminate the heredoc
 * @param shell Shell structure for exit codes
 * @return 0 on success, EXIT_SIGINT if SIGINT is received, or 1 on error.
 */
static int	handle_heredoc(const char *delimiter, t_shell *shell)
{
	int	fd;

	fd = create_heredoc_pipe(delimiter, shell);
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
 * @param shell: Shell structure for signal handling
 * @return: 0 on success, 1 on error, EXIT_SIGINT if interrupted
 */
int	apply_redirections(t_redir *redirs, t_shell *shell)
{
	t_redir	*curr;
	int		ret;

	curr = redirs;
	while (curr)
	{
		if (g_signal_received == SIGINT)
		{
			exit_codes(shell, 130, NULL);
			return (EXIT_SIGINT);
		}
		if (curr->type == TOKEN_REDIR_IN)
			ret = open_and_dup(curr->file, O_RDONLY, STDIN_FILENO);
		else if (curr->type == TOKEN_REDIR_OUT)
			ret = open_and_dup(curr->file, O_WRONLY | O_CREAT
					| O_TRUNC, STDOUT_FILENO);
		else if (curr->type == TOKEN_REDIR_APPEND)
			ret = open_and_dup(curr->file, O_WRONLY | O_CREAT
					| O_APPEND, STDOUT_FILENO);
		else if (curr->type == TOKEN_HEREDOC)
			ret = handle_heredoc(curr->file, shell);
		else
			ret = 0;
		if (ret)
			return (ret);
		curr = curr->next;
	}
	return (0);
}
