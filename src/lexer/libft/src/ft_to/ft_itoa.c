/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:07:22 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/31 12:09:27 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocates (with malloc(3)) and returns a string representing the integer
	received as an argument. Negative numbers must be handled.

PARAMETERS
	n: the integer to convert.

RETURN VALUE
	The string representing the integer. NULL if the allocation fails.
*/

#include "libft.h"

static int	ft_size(unsigned int n)
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

static unsigned int	ft_convert(int n)
{
	unsigned int	i;

	if (n < 0)
		i = (-n);
	else
		i = n;
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	i;
	char			*result;
	int				size;

	i = ft_convert(n);
	size = ft_size(i);
	if (n < 0)
		size += 1;
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	size -= 1;
	while (i > 0 && size)
	{
		result[size] = (i % 10) + '0';
		i /= 10;
		size--;
	}
	result[size] = (i % 10) + '0';
	if (n < 0)
		result[0] = '-';
	return (result);
}
