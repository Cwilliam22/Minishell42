/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:37:49 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/10 16:47:30 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <stdio.h>

ssize_t	ft_putnbr(int n)
{
	long	nbr;
	size_t	iter;

	iter = 0;
	nbr = n;
	if (n <= -2147483648)
		return (11);
	if (nbr < 0)
	{
		iter += ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		iter += ft_putnbr(nbr / 10);
		iter += ft_putnbr(nbr % 10);
	}
	if (nbr < 10)
	{
		iter += ft_putchar(nbr + '0');
	}
	return (iter);
}

ssize_t	ft_put_u_nbr(unsigned long nbr)
{
	size_t	iter;

	iter = 0;
	if (nbr <= 0)
	{
		iter += ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		iter += ft_putnbr(nbr / 10);
		iter += ft_putnbr(nbr % 10);
	}
	if (nbr < 10)
	{
		iter += ft_putchar(nbr + '0');
	}
	return (iter);
}

/*
#include <stdio.h>
int	main(void)
{
	int c = -42;
	size_t	a;

	a = ft_putnbr(-42);
	printf("\n %zd \n", a);
	return (0);
}
*/

/*
int main(void)
{
	int c = 42;
	size_t	a;

	a = ft_put_u_nbr(c);
	printf("\n %zd \n", a);
	return (0);
}
*/

// (l.24) Return 11 parce que -2147483648 est composé de 11 caractères

//Revoire récursive ligne 32 et 33
//utilise un "long" pour gérer les overflows
//"long" a une plus grande caopacité que le "int" (sécurité)
