/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:24:27 by alfavre           #+#    #+#             */
/*   Updated: 2025/07/06 11:50:50 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Find the matching closing quote for a given opening quote
 * @param str: String to search in
 * @param start: Position of opening quote
 * @return: Position of closing quote or -1 if not found
 */
int	find_matching_quote(char *str, int start)
{
	char	quote_char;
	int		i;

	if (!str || start < 0 || !str[start])
		return (-1);
	quote_char = str[start];
	if (quote_char != '\'' && quote_char != '"')
		return (-1);
	i = start + 1;
	while (str[i])
	{
		if (str[i] == quote_char)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * Append a character to a string (creates new string)
 * @param str: Original string (will be freed)
 * @param c: Character to append
 * @return: New string with character appended or NULL on error
 */
char	*append_char_to_str(char *str, char c)
{
	char	*result;
	char	temp[2];

	if (!str)
		return (NULL);
	temp[0] = c;
	temp[1] = '\0';
	result = ft_strjoin(str, temp);
	free(str);
	return (result);
}

/**
 * Join two strings and free them
 * @param str1: First string (will be freed)
 * @param str2: Second string (will be freed)
 * @return: Joined string or NULL on error
 */
char	*join_and_free(char *str1, char *str2)
{
	char	*result;

	if (!str1 || !str2)
	{
		free(str1);
		free(str2);
		return (NULL);
	}
	result = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (result);
}

/**
 * Check if character is valid for variable names
 * @param c: Character to check
 * @return: 1 if valid, 0 otherwise
 */
int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}
