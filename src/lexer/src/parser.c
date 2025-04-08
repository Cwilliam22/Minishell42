/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:58:23 by alfavre           #+#    #+#             */
/*   Updated: 2025/04/08 15:52:36 by alfavre          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redir	*new_redirection(t_token_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->next = NULL;
	return (redir);
}

void	add_redirection(t_command *cmd, t_redir *new)
{
	t_redir	*curr;

	if (!cmd->redirections)
	{
		cmd->redirections = new;
		return ;
	}
	curr = cmd->redirections;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

int	count_args(t_token *tokens)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = tokens;
	while (curr && curr->type == TOKEN_WORD)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}
