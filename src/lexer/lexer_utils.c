/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:34:20 by alexis            #+#    #+#             */
/*   Updated: 2025/07/08 21:50:20 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if character is an operator
 * @param c: Character to check
 * @return: 1 if operator, 0 otherwise
 */
int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * Check if character is whitespace
 * @param c: Character to check
 * @return: 1 if whitespace, 0 otherwise
 */
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/**
 * Skip whitespace characters
 * @param input: Input string
 * @param i: Current position
 * @return: New position after whitespace
 */
int	skip_whitespace(char *input, int i)
{
	while (input[i] && is_whitespace(input[i]))
		i++;
	return (i);
}

/**
 * Extract a word token (handles quotes)
 * @param input: Input string
 * @param start: Start position
 * @param end: Pointer to store end position
 * @return: Word string or NULL on error
 */
char	*extract_word(char *input, int start, int *end)
{
	int		i;
	char	quote_char;

	i = start;
	quote_char = '\0';
	while (input[i])
	{
		if (quote_char == '\0')
		{
			if (input[i] == '\'' || input[i] == '"')
				quote_char = input[i];
			else if (is_whitespace(input[i]) || is_operator(input[i]))
				break ;
		}
		else if (input[i] == quote_char)
			quote_char = '\0';
		i++;
	}
	*end = i;
	return (ft_strndup(input + start, i - start));
}

/**
 * Extract an operator token
 * @param input: Input string
 * @param start: Start position
 * @param end: Pointer to store end position
 * @return: Operator string or NULL on error
 */
char	*extract_operator(char *input, int start, int *end)
{
	char	*op;

	if (input[start] == '>' && input[start + 1] == '>')
	{
		*end = start + 2;
		op = ft_strdup(">>");
	}
	else if (input[start] == '<' && input[start + 1] == '<')
	{
		*end = start + 2;
		op = ft_strdup("<<");
	}
	else
	{
		*end = start + 1;
		op = malloc(2);
		if (op)
		{
			op[0] = input[start];
			op[1] = '\0';
		}
	}
	return (op);
}
