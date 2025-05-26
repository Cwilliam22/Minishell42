/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:10:57 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/30 15:58:43 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Applies the function f to each character of the string s, passing its
	index as the first argument and the character itself as the second. A new
	string is created (using malloc(3)) to collect the results from
	the successive applications of f.

PARAMETERS
	s: The string on which to iterate.
	f: The function to apply to each character.

RETURN VALUE
	The string created from the successive applications of ’f’.
	Returns NULL if the allocation fails.
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	index;
	size_t			size;

	if (!s)
		return (NULL);
	index = 0;
	size = ft_strlen(s);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	while (s[index])
	{
		result[index] = (*f)(index, s[index]);
		index++;
	}
	result[index] = '\0';
	return (result);
}
