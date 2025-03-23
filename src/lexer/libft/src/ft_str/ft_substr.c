/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:17:08 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/31 11:52:03 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocate (with malloc(3)) and return a substring from the string 's'.
	This new string begins at index 'start' and is of maximum size 'len'.

RETURN VALUE
	A pointer to the new substring from 's'. NULL if the allocation doesn't
	work.
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	char	*cpy;
	size_t	length;

	cpy = (char *)(s + start);
	if (!s || ft_strlen(s) == 0)
		return (ft_strdup(s));
	else if (start > ft_strlen(s))
	{
		length = 0;
		cpy = (char *)s;
	}
	else if (len > ft_strlen(s + start))
		length = ft_strlen(s + start);
	else
		length = len;
	ptr = malloc(sizeof(char) * (length + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, cpy, length + 1);
	return (ptr);
}
