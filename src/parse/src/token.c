/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:08:07 by alfavre           #+#    #+#             */
/*   Updated: 2025/03/17 16:12:37 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief Main function to lexical analyse
 * @param input The string to analyse
 * @return The list of token
 */
t_token	*tokenize(char *str)
{
	t_token	*list;
	int		index;

	list = NULL;
	index = 0;
	while (isspace(str[index]))
		index++;
	
}
