/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adresse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:13:42 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/10 16:44:41 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static	ssize_t	ft_hexa(long unsigned adresse)
{
	ssize_t	value;

	value = 0;
	if (adresse > 15)
	{
		value += ft_hexa(adresse / 16);
		value += ft_hexa(adresse % 16);
	}
	else
	{
		if (adresse < 10)
			value += ft_putchar(adresse + '0');
		else
			value += ft_putchar(adresse - 10 + 'a');
	}
	return (value);
}

ssize_t	ft_adresse(void *adresse)
{
	size_t	value;

	value = 0;
	if (!adresse)
	{
		value = ft_putstr("0x0");
	}
	else
	{
		value += ft_putstr("0x");
		value += ft_hexa((long unsigned) adresse);
	}
	return (value);
}

/*
int main(void)
{
    int variable = 42;
    void *adresse = &variable;

    ft_adresse(adresse);
    ft_putchar('\n');

    return 0;
}
*/
