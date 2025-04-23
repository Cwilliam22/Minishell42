/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:40:37 by alexis            #+#    #+#             */
/*   Updated: 2025/04/23 14:54:27 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_redirection(t_redir *redirections)
{
	t_redir	*ptr;

	while (redirections)
	{
		ptr = redirections;
		redirections = redirections->next;
		free(ptr->file);
		free(ptr);
	}
}

void	free_command(t_command *cmd)
{
	int		i;

	i = 0;
	if (cmd->name)
		free(cmd->name);
	if (cmd->args)
	{
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	if (cmd->redirections)
		free_redirection(cmd->redirections);
	free(cmd);
}

void	free_commands(t_command *cmd)
{
	t_command	*ptr;

	while (cmd)
	{
		ptr = cmd;
		cmd = cmd->next;
		free_command(ptr);
	}
}