/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:47:19 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/22 18:15:24 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The strdup() function returns a pointer to a new string which is a
	duplicate of the string s. Memory for the new string is obtained with
	malloc(3), and can be freed with free(3).

RETURN VALUE
	On success, the strdup() function returns a pointer to the duplicated
	string. It returns NULL if insufficient memory was available, with errno
	set to indicate the error.
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*ptr;
	size_t			length;

	length = ft_strlen(s) + 1;
	ptr = malloc(sizeof(char) * length);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, length);
	return (ptr);
}
