/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:48:18 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/10 16:44:52 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

ssize_t	ft_hexa_conv(unsigned int c, int index)
{
	char	*base;
	size_t	value;

	value = 0;
	if (index == 1)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (c > 15)
	{
		value += ft_hexa_conv(c / 16, index);
		value += ft_hexa_conv(c % 16, index);
	}
	else
	{
		value += ft_putchar(base[c]);
	}
	return (value);
}

/*
int main(void)
{
	int c = -42;
	ft_hexa_conv(-42;)
	return (0);
}
*/
