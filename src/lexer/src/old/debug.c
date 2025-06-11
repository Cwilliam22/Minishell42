/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:28:30 by alexis            #+#    #+#             */
/*   Updated: 2025/04/09 15:10:57 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/lexer.h"

void	print_token(t_token *token)
{
	char	*type_names[] = {
		"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND", "HEREDOC", "EOF"
	};
	printf("Type: %-12s | Valeur: '%s'\n", type_names[token->type], token->value);
}

void	print_all_tokens(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	printf("\n=== TOKENS ===\n");
	while (curr)
	{
		print_token(curr);
		curr = curr->next;
	}
	printf("==============\n\n");
}

void	print_redirection(t_redir *redir)
{
	char	*type_names[] = {
		"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND", "HEREDOC", "EOF"
	};
	printf("Redirection: %-12s | Fichier: '%s'\n",
		type_names[redir->type], redir->file);
}

void	print_command(t_command *cmd)
{
	int		i;
	t_redir	*redir;

	i = 0;
	printf("Command: '%s'\n", cmd->name);
	printf("Arguments:\n");
	while (cmd->args[i])
	{
		printf("	Arg[%d]: '%s'\n", i, cmd->args[i]);
		i++;
	}
	printf("Redirections:\n");
	redir = cmd->redirections;
	if (!redir)
		printf("	Aucune\n");
	while (redir)
	{
		print_redirection(redir);
		redir = redir->next;
	}
}

void	print_all_commands(t_command *cmd)
{
	t_command	*curr;
	int			cmd_num;

	curr = cmd;
	cmd_num = 0;
	printf("\n=== COMMANDES ===\n");
	while (curr)
	{
		printf("\nCommand #%d:\n", cmd_num++);
		print_command(curr);
		curr = curr->next;
	}
	printf("==================\n\n");
}