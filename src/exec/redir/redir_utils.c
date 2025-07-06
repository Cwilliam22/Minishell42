/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:14:56 by root              #+#    #+#             */
/*   Updated: 2025/07/06 14:55:29 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Create a new redirection structure
 * @param type: Type of redirection (e.g., REDIR_IN, REDIR_OUT, etc.)
 * @param file: File associated with the redirection
 * @return: Pointer to the newly created t_redir structure, or NULL on failure
 */
t_redir	*create_redirection(int type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
		return (free(redir), NULL);
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

/**
 * Add a new redirection to the end of the linked list of redirections
 * @param head: Pointer to the head of the linked list
 * @param new_redir: New redirection to add
 */
void	add_redirection(t_redir **head, t_redir *new_redir)
{
	t_redir	*current;

	if (!head || !new_redir)
		return ;
	if (!*head)
	{
		*head = new_redir;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

/**
 * Free the memory allocated for a linked list of redirections
 * @param redirections: Pointer to the head of the linked list
 */
void	free_redirections(t_redir *redirections)
{
	t_redir	*current;
	t_redir	*next;

	current = redirections;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
}

/**
 * Opens a file and duplicates its file descriptor to the specified standard
 * file descriptor (stdin or stdout).
 * @param file The file to open.
 * @param flags The flags to use when opening the file.
 * @param stdfd The standard file descriptor to duplicate to (STDIN_FILENO or
 * STDOUT_FILENO).
 * @return 0 on success, 1 on error.
 */
int	open_and_dup(const char *file, int flags, int stdfd)
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

/**
 * Duplicates a file descriptor to a standard file descriptor and closes the
 * original file descriptor.
 * @param fd The file descriptor to duplicate.
 * @param stdfd The standard file descriptor to duplicate to (STDIN_FILENO or
 * STDOUT_FILENO).
 * @param err The error message to print if dup2 fails.
 * @return 0 on success, 1 on error.
 */
int	dup_and_close(int fd, int stdfd, const char *err)
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
