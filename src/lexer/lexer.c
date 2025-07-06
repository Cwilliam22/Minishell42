/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:15:11 by root              #+#    #+#             */
/*   Updated: 2025/07/04 15:33:53 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Get the type of a token based on its value
 * @param str: Token string
 * @return: Token type
 */
static int	get_token_type(char *str)
{
	if (!str)
		return (TOKEN_EOF);
	if (ft_strcmp(str, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(str, "<") == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strcmp(str, ">") == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strcmp(str, ">>") == 0)
		return (TOKEN_REDIR_APPEND);
	if (ft_strcmp(str, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (str[0] == '$' && str[1] != '\0')
		return (TOKEN_VAR);
	if (str[0] == '\0')
		return (TOKEN_EOF);
	return (TOKEN_WORD);
}

/**
 * Create a new token and add it to the token list
 * @param value: Token value
 * @param type: Token type
 * @return: New token or NULL on error
 */
static t_token	*create_and_add_token(char *token_value, t_token **head)
{
	t_token	*new_token;

	new_token = create_token(token_value, get_token_type(token_value));
	if (!new_token)
		return (NULL);
	add_token(head, new_token);
	return (new_token);
}

/**
 * Extract a word token from the input string
 * @param input: Input string
 * @param start: Start position
 * @param end: Pointer to store end position
 * @return: Extracted word or NULL on error
 */
static char	*extract_next_token(char *input, int i, int *end)
{
	if (is_operator(input[i]))
		return (extract_operator(input, i, end));
	else
		return (extract_word(input, i, end));
}

/**
 * Main tokenization function
 * @param input: Input string to tokenize
 * @return: Head of token list or NULL on error
 */
t_token	*tokenize(char *input)
{
	t_token	*head;
	char	*token_value;
	int		i;
	int		end;

	if (!input)
		return (NULL);
	head = NULL;
	i = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		token_value = extract_next_token(input, i, &end);
		if (!token_value || !create_and_add_token(token_value, &head))
			return (free(token_value), free_tokens(head), NULL);
		free(token_value);
		i = end;
	}
	return (head);
}
