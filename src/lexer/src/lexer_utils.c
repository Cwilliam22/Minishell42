/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:25:00 by alfavre           #+#    #+#             */
/*   Updated: 2025/03/23 15:35:40 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Define if a character is a shell operator
 * @param c The character to define
 * @return 1 if c is an operator, 0 otherwise
 */
int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

/**
 * @brief Ignore spaces in a string
 * @param str The string
 * @return A pointer to the first non-space character
 */
char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str && (isspace(*str)))
		str++;
	return (str);
}

/**
 * @brief Check if the character is a delimiter (space or operator)
 * @param c The character to check
 * @return 1 if it's a delimiter, 0 otherwise
 */
int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0'
		|| is_operator_char(c));
}

/**
 * @brief This function allows you to duplicate at most size
 * characters of the string passed as a parameter.
 * @param src The adress of the string to duplicate
 * @param n Max n character to duplicate
 * @return If there is enough memory to produce the new string,
 * the function returns the address of the duplicate string.
 * Otherwise, a null pointer will be returned.
 */
static char	*ft_strndup(char *src, int n)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * n);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, src, n);
	return (ptr);
}

/**
 * @brief Extract a word until the next delimiter, by managing quotes
 * @param str The string to extract from
 * @return The extracted word 
 */
char	*extract_word(char *str)
{
	int		length;
	char	quote;
	char	*word;

	if (!str || !*str)
		return (NULL);
	length = 0;
	quote = 0;
	while (str[length] && (!is_delimiter(str[length]) || quote))
	{
		if ((str[length] == '\'' || str[length] == '\"')
			&& (!quote || quote == str[length]))
		{
			if (quote)
				quote = 0;
			else
				quote = str[length];
		}
		length++;
	}
	word = ft_strndup(str, (length + 1));
	return (word);
}
