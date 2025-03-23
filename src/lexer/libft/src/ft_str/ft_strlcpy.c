/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:02:23 by alfavre           #+#    #+#             */
/*   Updated: 2024/12/25 10:06:32 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief The strlcpy() function copy strings. It is designed to be safer,
 * more consistent, and less error prone replacements for strncpy(3).
 * Unlike this function, strlcpy() take the full size of the buffer
 * (not just the length) and guarantee to NUL-terminate the result. Note that
 * a byte for the NUL should be included in size.  Also note that strlcpy()
 * operate on true “C” strings.  This means that for strlcpy() src must be
 * NUL-terminated. The strlcpy() function copies up to size - 1 characters
 * from the NUL-terminated string src to dst, NUL-terminating the result.
 * @param dst The destination buffer
 * @param src The source to copy
 * @param size The size of the destination buffer
 * @return The strlcpy() function return the total length of the string it
 * tried to create. For strlcpy() that means the length of src.
*/
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size)
	{
		while (src[i] && i < (size -1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
