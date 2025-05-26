/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:58:23 by alfavre           #+#    #+#             */
/*   Updated: 2025/04/09 12:06:00 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/lexer.h"

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

char	**extract_args(t_token **tokens, int arg_count)
{
	char	**args;
	int		i;
	t_token	*curr;

	i = 0;
	curr = *tokens;
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	while (i < arg_count && curr && curr->type == TOKEN_WORD)
	{
		args[i++] = ft_strdup(curr->value);
		curr = curr->next;
	}
	args[i] = NULL;
	*tokens = curr;
	return (args);
}
