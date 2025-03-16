/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:25:27 by alfavre           #+#    #+#             */
/*   Updated: 2024/12/25 09:59:48 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Print a number in hexadecimal with the x in lowercase.
 * @param nbr The number to print in hexadecimal with x in lowercase.
 * @return The value of the nbr in hexadecimal.
 */
int	ft_printf_hex_lowercase(unsigned long long nbr)
{
	int	nb_char;
	int	temp;

	nb_char = 0;
	if (nbr == 0)
		return (ft_printf_char('0'));
	if (nbr >= 16)
	{
		nb_char += ft_printf_hex_lowercase(nbr / 16);
		nb_char += ft_printf_hex_lowercase(nbr % 16);
	}
	else
	{
		if (nbr < 10)
			temp = ft_printf_char(nbr + '0');
		else
			temp = ft_printf_char(nbr - 10 + 'a');
		if (temp == -1)
			return (temp);
		nb_char += temp;
	}
	return (nb_char);
}

/**
 * @brief Print a number in hexadecimal with the x in uppercase.
 * @param nbr The number to print in hexadecimal
 * @return The value of the nbr in hexadecimal
 */
int	ft_printf_hex_uppercase(unsigned long long nbr)
{
	int	nb_char;
	int	temp;

	nb_char = 0;
	if (nbr == 0)
		return (ft_printf_char('0'));
	if (nbr >= 16)
	{
		nb_char += ft_printf_hex_uppercase(nbr / 16);
		nb_char += ft_printf_hex_uppercase(nbr % 16);
	}
	else
	{
		if (nbr < 10)
			temp = ft_printf_char(nbr + '0');
		else
			temp = ft_printf_char(nbr - 10 + 'A');
		if (temp == -1)
			return (temp);
		nb_char += temp;
	}
	return (nb_char);
}

/**
 * @brief Print the pointer's address
 * @param ptr The pointer to print his address
 * @return The value of the pointer's address in hexadecimal
 */
int	ft_printf_pointer(void *ptr)
{
	int					nb_char;
	unsigned long long	adress;

	nb_char = 0;
	adress = (unsigned long long)ptr;
	nb_char += ft_printf_string("0x");
	nb_char += ft_printf_hex_lowercase(adress);
	return (nb_char);
}
