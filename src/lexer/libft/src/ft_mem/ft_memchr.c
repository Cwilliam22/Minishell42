/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:07:22 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/21 18:28:23 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The memchr() function scans the initial n bytes of the memory area
	pointed to by s for the first instance of c. Both c and the bytes of
	the memory area pointed to by s are interpreted as unsigned char.

RETURN VALUE
	The memchr() and memrchr() functions return a pointer  to  the  matching
	byte or NULL if the character does not occur in the given memory area.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (*(ptr) == (unsigned char)c)
			return (ptr);
		ptr++;
		i++;
	}
	return (NULL);
}
