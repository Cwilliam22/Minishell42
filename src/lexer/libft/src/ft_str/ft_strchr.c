/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:19:43 by alfavre           #+#    #+#             */
/*   Updated: 2024/11/10 10:11:13 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @brief The strchr() function returns a pointer to the first occurrence of the
* character c in the string s. Here "character" means "byte"; these functions
* do not work with wide or multibyte characters.
*
* @return The strchr() and strrchr() functions return a pointer to the matched
* character or NULL if the character is not found.  The terminating null
* byte is considered part of the string, so that if c is specified as '\0',
* these functions return a pointer to the terminator.
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
