/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:23:27 by alfavre           #+#    #+#             */
/*   Updated: 2024/12/25 09:59:53 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Print an integer with the function itoa
 * @param nbr The number to print
 * @return The number of charater printed. -1 if there is an error.
 */
int	ft_printf_int(int nbr)
{
	char	*s;
	int		nb_char;

	s = ft_itoa(nbr);
	nb_char = ft_printf_string(s);
	free(s);
	return (nb_char);
}

/**
 * @brief Function to count the number of digits in a number
 * @param n a unsigned integer
 * @return the number of digits
 */
static int	ft_uint_size(unsigned int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

/**
 * @brief Print a unsigned integer
 * @param nbr The number to print
 * @return The number of character printed. -1 if there is an error.
 */
int	ft_printf_uint(unsigned int nbr)
{
	char	*s;
	size_t	index;
	int		nb_char;

	index = ft_uint_size(nbr);
	s = malloc(sizeof(char *) * (index + 1));
	if (!s)
		return (-1);
	s[index--] = '\0';
	while (nbr > 0 && index)
	{
		s[index--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	s[index] = (nbr % 10) + '0';
	nb_char = ft_printf_string(s);
	free(s);
	return (nb_char);
}
