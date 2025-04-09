/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:45:41 by alfavre           #+#    #+#             */
/*   Updated: 2025/04/09 12:58:51 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*new_token(t_token_type type, char *value)
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

static void	add_token(t_token **tokens, t_token *new)
{
	t_token *current;

	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new;
}

static t_token	*handle_redirection(char *input, int *i)
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


t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;
	char	*word;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		if (is_whitespace(input[i]))
			i++;
		if (input[i] == '|')
		{
			add_token(&tokens, new_token(TOKEN_PIPE, "|"));
			i++;
		}
		else if (input[i] == '<' || input[i] == '>')
			add_token(&tokens, handle_redirection(input, &i));
		else
		{
			word = extract_word(input, &i);
			if (word)
			{
				add_token(&tokens, new_token(TOKEN_WORD, word));
				free(word);
			}
		}
	}
	add_token(&tokens, new_token(TOKEN_EOF, "EOF"));
	return (tokens);
}

void	free_tokens(t_token *tokens)
{
	t_token	*ptr;

	while (tokens)
	{
		ptr = tokens;
		tokens = tokens->next;
		free(ptr->value);
		free(ptr);
	}
}
