/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:38:52 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/10 17:36:53 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

ssize_t	ft_specifi(const char *str, va_list *args, size_t *i)
{
	*i += 1;
	if (*(str + 1) == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (*(str + 1) == 'c')
		return (ft_putchar((char)va_arg(*args, int)));
	else if (*(str + 1) == 'p')
		return (ft_adresse(va_arg(*args, void *)));
	else if (*(str + 1) == 'd')
		return (ft_putnbr(va_arg(*args, int)));
	else if (*(str + 1) == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	else if (*(str + 1) == 'u')
		return (ft_put_u_nbr(va_arg(*args, unsigned int)));
	else if (*(str + 1) == 'x')
		return (ft_hexa_conv(va_arg(*args, int), 1));
	else if (*(str + 1) == 'X')
		return (ft_hexa_conv(va_arg(*args, int), 0));
	else if (*(str + 1) == '%')
		return (ft_putchar('%'));
	else if (*(str + 1) == '\0')
		return (0);
	else
		return (-1);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;
	int		len;
	int		more;

	va_start(args, format);
	i = 0;
	len = 0;
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%')
			more = ft_specifi(format + i, &args, &i);
		else
			more = ft_putchar(format[i]);
		if (more >= 0)
			len += more;
		else
			return (-1);
		i++;
	}
	va_end(args);
	return (len);
}

/*
#include <stdio.h>

int	main(void)
{
	ft_printf("Hello ");
	ft_printf("[%d]", -2147483650);
	ft_printf("!\n");
	return (0);
}
*/

// Déclare une variable va_list pour gérer les arguments
// Compteur pour parcourir la chaîne de format
// Compte les caractères imprimés
// Si on rencontre "%%", on affiche un '%'
// Sauter le deuxième '%'
// Nettoie va_list après l'utilisation (libère la mémoire allouée)
// Return le nbr total de caractères 
