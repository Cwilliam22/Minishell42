/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:20:54 by alfavre           #+#    #+#             */
/*   Updated: 2024/12/28 10:56:49 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @brief The strrchr() function returns a pointer to the last occurrence of the
* character c in the string s. Here "character" means "byte"; these functions
* do not work with wide or multibyte characters.
*
* @return The strchr() and strrchr() functions return a pointer to the matched
* character or NULL if the character is not found.  The terminating null
* byte is considered part of the string, so that if c is specified as '\0',
* these functions return a pointer to the terminator.
*/
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)(s + ft_strlen(s));
	while (ptr != s)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr--;
	}
	if (*ptr == (char)c)
		return (ptr);
	return (NULL);
}
