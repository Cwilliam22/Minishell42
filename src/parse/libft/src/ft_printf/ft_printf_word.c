/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:10:05 by alfavre           #+#    #+#             */
/*   Updated: 2024/12/25 09:59:59 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Print a character on the standard output with the function "write".
 * @param c The character to print on the standard output.
 * @return Upon successful completion the number of bytes which were written is
 * 	returned. Otherwise, a -1 is returned and the global variable errno is
 * 	set to indicate the error.
 */
int	ft_printf_char(char c)
{
	return (write(1, &c, 1));
}

/**
 * @brief Print a string on the standard output with the function
 * 	"ft_printf_char".
 * @param s The string to print on the standard output.
 * @return Upon successful completion the number of bytes which were written is
 * 	returned. Otherwise, a -1 is returned.
 */
int	ft_printf_string(char *s)
{
	int	nb_char;
	int	temp;

	nb_char = 0;
	temp = 0;
	if (!s)
	{
		return (ft_printf_string("(null)"));
	}
	while (*s)
	{
		temp = ft_printf_char(*s);
		if (temp == (-1))
			return (-1);
		else
			nb_char += temp;
		s++;
	}
	return (nb_char);
}
