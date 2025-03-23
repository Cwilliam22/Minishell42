/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:17:26 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/30 17:30:33 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
	specified in ’set’ removed from the beginning and the end of the string.

PARAMETERS
	s1: The string to be trimmed.
	set: The reference set of characters to trim.

RETURN VALUE
	The trimmed string. NULL if the allocation fails.
*/

#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	length;
	size_t	i;
	size_t	start;
	char	*result;

	length = ft_strlen(s1);
	i = 0;
	start = 0;
	while (ft_isset(s1[i++], set))
		length--;
	start = i - 1;
	i = ft_strlen(s1) - 1;
	while (ft_isset(s1[i--], set) && length > 0)
		length--;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1 + start, length + 1);
	return (result);
}
