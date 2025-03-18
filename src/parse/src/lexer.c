/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:08:07 by alfavre           #+#    #+#             */
/*   Updated: 2025/03/18 14:19:58 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Main function to lexical analyse
 * @param input The string to analyse
 * @return The list of token
 */
t_token	*tokenize(char *str)
{
	t_token	*list;
	t_token	*operator;
	char	quote_type;
	char	*quoted_str;
	char	*word;
	int		index;

	list = NULL;
	index = 0;
	while (isspace(str[index]))
		index++;
	if (is_operator_char(str[index]))
	{
		
	}
	
}
