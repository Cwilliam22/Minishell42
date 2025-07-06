/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:49:09 by alexis            #+#    #+#             */
/*   Updated: 2025/07/04 16:32:10 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Print pipe syntax error message
 * @param token: Token that caused the error
 */
static int	check_pipe_syntax(t_token *current)
{
	if (!current->next || current->next->type == TOKEN_PIPE)
		return (print_syntax_error("|"), 2);
	return (1);
}

/**
 * Print redir syntax error message
 * @param token: Token that caused the error
 */
static int	check_redir_syntax(t_token *current)
{
	if (!current->next || current->next->type != TOKEN_WORD)
	{
		if (current->next)
			print_syntax_error(current->next->value);
		else
			print_syntax_error("newline");
		return (2);
	}
	return (1);
}

/**
 * Check syntax errors in token list
 * @param tokens: Head of token list
 * @return: 1 if syntax is valid, the value of the synthax error otherwise
 */
int	check_token_syntax(t_token *tokens)
{
	t_token	*current;
	int		result;

	if (!tokens)
		return (1);
	current = tokens;
	result = 1;
	if (current->type == TOKEN_PIPE)
		return (print_syntax_error("|"), 2);
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			result = check_pipe_syntax(current);
		else if (current->type >= TOKEN_REDIR_IN
			&& current->type <= TOKEN_HEREDOC)
			result = check_redir_syntax(current);
		if (result != 1)
			return (result);
		current = current->next;
	}
	return (1);
}
