/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:04:08 by alfavre           #+#    #+#             */
/*   Updated: 2025/03/31 14:56:09 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Handle content between quotes
 * @param str The string with quotes
 * @param pos The actual position in the string str
 * @param quote_type The type of quote (' or ")
 * @return The content between the quotes (to free)
 */
char	*handle_quotes(char *str, int *pos, char quote_type)
{
	int		start;
	int		i;
	char	*quoted_str;

	start = *pos;
	while (str[*pos] && str[*pos] != quote_type)
		(*pos)++;
	if (str[*pos] == quote_type)
		(*pos)++;
	quoted_str = malloc(sizeof(char) * (*pos - start + 1));
	if (!quoted_str)
		return (NULL);
	i = 0;
	while (start < (*pos - 1))
		quoted_str[i++] = str[start++];
	quoted_str[i] = '\0';
	return (quoted_str);
}

/**
 * @brief Handle redirection operators and pipes
 * @param token The token to configure
 * @param curr The current character
 * @param next The next character
 * @param pos The current index
 * @return The extract word (to free)
 */
handle redirection

handle output logic

handle paren

/**
 * @brief Handle 
 */
handle escape