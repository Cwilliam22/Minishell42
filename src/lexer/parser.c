/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:31:41 by root              #+#    #+#             */
/*   Updated: 2025/07/04 16:13:23 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Count number of pipe tokens in the list
 * @param tokens: Head of token list
 * @return: Number of pipe tokens
 */
static int	count_pipes(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 0;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

/**
 * Split token list by pipes
 * @param tokens: Head of token list
 * @return: Array of token lists (one per command)
 */
static t_token	**split_by_pipes(t_token *tokens)
{
	t_token	**commands;
	t_token	*current;
	int		i;

	if (!tokens)
		return (NULL);
	commands = malloc(sizeof(t_token *) * (count_pipes(tokens) + 2));
	if (!commands)
		return (NULL);
	current = tokens;
	i = 0;
	commands[i] = current;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			commands[++i] = current->next;
		current = current->next;
	}
	commands[i + 1] = NULL;
	return (commands);
}

/**
 * Parse a single command from tokens
 * @param tokens: Starting token for this command
 * @return: Command structure or NULL on error
 */
static t_cmd	*parse_single_command(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmd;

	if (!tokens)
		return (NULL);
	if (strcmp(tokens->value, "$?") == 0)
	{
		free(tokens->value);
		tokens->value = ft_itoa(shell->exit_status);
	}
	cmd = create_command();
	if (!cmd)
		return (NULL);
	if (!extract_arguments(tokens, cmd, shell))
		return (free_commands(cmd), NULL);
	if (!extract_redirections(tokens, cmd))
		return (free_commands(cmd), NULL);
	return (cmd);
}

/**
 * Main parsing function - converts tokens to command list
 * @param tokens: Head of token list
 * @param shell: Shell structure
 * @return: Head of command list or NULL on error
 */
t_cmd	*parse_tokens(t_token *tokens, t_shell *shell)
{
	t_cmd		*head;
	t_cmd		*cmd;
	t_token		**cmd_tokens;
	int			i;

	if (!tokens)
		return (NULL);
	cmd_tokens = split_by_pipes(tokens);
	if (!cmd_tokens)
		return (NULL);
	head = NULL;
	i = 0;
	while (cmd_tokens[i])
	{
		cmd = parse_single_command(cmd_tokens[i], shell);
		if (!cmd)
			return (free_commands(head), free(cmd_tokens), NULL);
		add_command(&head, cmd);
		i++;
	}
	free(cmd_tokens);
	return (head);
}
