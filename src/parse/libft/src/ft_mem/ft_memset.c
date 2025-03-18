/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:13:56 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/30 16:12:33 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The memset() function writes len bytes of value c (converted to an
	unsigned char) to the string b.

RETURN VALUES
	The memset() function returns its first argument.
*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*ptr;

	ptr = b;
	while (len--)
	{
		*(char *)ptr++ = c;
	}
	return (b);
}
