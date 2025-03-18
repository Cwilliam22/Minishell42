/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:23:24 by alfavre           #+#    #+#             */
/*   Updated: 2025/03/18 14:20:05 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*skip_space(char *str);
char	*extract_word(char *str, int *pos);
char	*handle_quotes(char *str, int *pos, char quote_type);