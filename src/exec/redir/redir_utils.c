/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:14:56 by root              #+#    #+#             */
/*   Updated: 2025/06/19 12:15:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Redirection utilities */
t_redir	*create_redirection(int type, char *file)
{
	t_redir *redir;
	
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return NULL;
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return NULL;
	}
	redir->fd = -1;
	redir->next = NULL;
	return redir;
}

void	add_redirection(t_redir **head, t_redir *new_redir)
{
	t_redir *current;
	
	if (!head || !new_redir)
		return;
	if (!*head)
	{
		*head = new_redir;
		return;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

void	free_redirections(t_redir *redirections)
{
	t_redir *current, *next;
	
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