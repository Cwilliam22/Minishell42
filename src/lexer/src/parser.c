/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:49:16 by alexis            #+#    #+#             */
/*   Updated: 2025/04/09 12:55:08 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void process_redirection(t_command *cmd, t_token **tokens)
{
	t_token_type	type;
	t_token			*curr;

	curr = *tokens;
	type = curr->type;
	curr = curr->next;
	if (curr && curr->type == TOKEN_WORD)
	{
		add_redirection(cmd, new_redirection(type, curr->value));
		curr = curr->next;
	}
	*tokens = curr;
}

static t_command	*parse_simple_command(t_token **tokens, t_env *env, int last_exit_code)
{
	t_command	*cmd;
	t_token		*curr;
	int			arg_count;
	(void)env;
	(void)last_exit_code;

	curr = *tokens;
	cmd = new_command();
	if (!cmd)
		return (NULL);
	if (!curr || curr->type != TOKEN_WORD)
		return (free(cmd), NULL);
	arg_count = count_args(curr);
	cmd->args = extract_args(&curr, arg_count);
	cmd->name = ft_strdup(cmd->args[0]);
	while (curr && (curr->type == TOKEN_REDIR_IN || curr->type == TOKEN_REDIR_OUT
		|| curr->type == TOKEN_APPEND || curr->type == TOKEN_HEREDOC))
		process_redirection(cmd, &curr);
	*tokens = curr;
	return (cmd);
}
t_command	*parse(t_token *tokens, t_env *env, int last_exit_code)
{
	t_command	*head;
	t_command	*curr;
	t_command	*new_cmd;
	t_token		*current_token;

	head = NULL;
	curr = NULL;
	current_token = tokens;
	while (current_token && current_token->type != TOKEN_EOF)
	{
		new_cmd = parse_simple_command(&current_token, env, last_exit_code);
		if (new_cmd)
		{
			if (!head)
			{
				head = new_cmd;
				curr = head;
			}
			else
			{
				curr->next = new_cmd;
				curr = curr->next;
			}
		}
		if (current_token && current_token->type == TOKEN_PIPE)
			current_token = current_token->next;
	}
	return (head);
}
