/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:50:49 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/21 22:43:23 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The strnstr() function locates the first occurrence of the null-termi‐
	nated string little in the string big, where not more than len charac‐
	ters are searched. Characters that appear after a ‘\0’ character are
	not searched. Since the strnstr() function is a FreeBSD specific API,
	it should only be used when portability is not a concern.

RETURN VALUES
	If little is an empty string, big is returned; if little occurs nowhere
	in big, NULL is returned; otherwise a pointer to the first character of
	the first occurrence of little is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	start;

	i = 0;
	if (sizeof(little) == 0 || *little == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		start = 0;
		if (big[i] == little[start])
		{
			while (little[start] && big[i + start] == little[start]
				&& (i + start) < len)
				start++;
			if (little[start] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
