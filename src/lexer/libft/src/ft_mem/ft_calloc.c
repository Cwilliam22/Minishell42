/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:05:23 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/22 17:45:52 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The calloc() function allocates memory for an array of nmemb elements of
	size bytes each and returns a pointer to the allocated memory.
	The memory is set to zero. If nmemb or size is 0, then calloc() returns
	a unique pointer value that can later be successfully passed to free().

	If the multiplication of nmemb and size would result in integer overflow,
	then calloc() returns an error. By contrast, an integer overflow would not
	be detected in the following call to malloc(), with the result that an
	incorrectly sized block of memory would be allocated:

		malloc(nmemb * size);

RETURN VALUE
	The malloc(), calloc(), realloc(), and reallocarray() functions return a
	pointer to the allocated memory, which is suitably aligned for any type that
	fits into the requested size or less. On error, these functions return NULL
	and set errno. Attempting to allocate more than PTRDIFF_MAX bytes is
	considered an error, as an object that large could cause later pointer
	subtraction to overflow.

ERRORS
	calloc(), malloc(), realloc(), and reallocarray() can fail with the following
	error:

	ENOMEM Out of memory. Possibly, the application hit the RLIMIT_AS or
		RLIMIT_DATA limit described in getrlimit(2). Another reason could be
		that the number of mappings created by the caller process exceeded the
		limit specified by /proc/sys/vm/max_map_count.
*/

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	**result;

	result = malloc(nmemb * size);
	if (!result)
		return (NULL);
	ft_bzero(result, nmemb * size);
	return (result);
}
