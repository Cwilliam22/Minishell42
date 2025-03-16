/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:27:42 by alfavre           #+#    #+#             */
/*   Updated: 2024/12/25 10:00:05 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Function which redirects to the functions adapted to the character
 * after the %.
 * @param args The va_list created in the ft_printf function.
 * @param s The character after the %
 * @return The number of character printed. -1 if there is an error.
 */
int	ft_printf_args(va_list args, const char *s)
{
	if (*s == 'd' || *s == 'i')
		return (ft_printf_int(va_arg(args, int)));
	else if (*s == 'u')
		return (ft_printf_uint(va_arg(args, unsigned int)));
	else if (*s == 'c')
		return (ft_printf_char(va_arg(args, int)));
	else if (*s == 's')
		return (ft_printf_string(va_arg(args, char *)));
	else if (*s == 'p')
		return (ft_printf_pointer(va_arg(args, void *)));
	else if (*s == 'x')
		return (ft_printf_hex_lowercase(va_arg(args, unsigned int)));
	else if (*s == 'X')
		return (ft_printf_hex_uppercase(va_arg(args, unsigned int)));
	else
		return (ft_printf_char('%'));
}

/**
 * @brief Function that will mimic the original printf()
 * @param format The first or the only one string given in parameter
 * @param ... 0 or more parameters. Will be stock in a va_list.
 * @return The number of printed character or -1 if there is an error.
 */
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		nb_char;
	int		temp;

	if (!format)
		return (-1);
	if (*format == '\0')
		return (0);
	nb_char = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			temp = ft_printf_args(args, ((format++) + 1));
		else
			temp = ft_printf_char(*format);
		if (temp == -1)
			return (temp);
		nb_char += temp;
		format++;
	}
	va_end(args);
	return (nb_char);
}
