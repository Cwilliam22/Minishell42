/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:08:07 by alfavre           #+#    #+#             */
/*   Updated: 2025/04/06 11:40:51 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token *current;

	if (!*tokens)
		return (*tokens = new);
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new;
}

t_token	*handle_redirection(char *input, int *i)
{
	t_token_type	type;

	if (input[*i] == '<')
	{
		(*i)++;
		if (input[*i] == '<')
		{
			(*i)++;
			type = TOKEN_HEREDOC;
			return (new_token(type, "<<"));
		}
		return (type = TOKEN_REDIR_IN, new_token(type, "<"));
	}
	else if (input[*i] == '>')
	{
		(*i)++;
		if (input [*i] == '>')
		{
			(*i)++;
			type = TOKEN_APPEND;
			return (new_token(type, ">>"));
		}
		return (type = TOKEN_REDIR_OUT, new_token(type, ">"));
	}
	return (NULL);
}

