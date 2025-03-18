/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: williamcapt <williamcapt@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:01:20 by apiscopo          #+#    #+#             */
/*   Updated: 2025/02/06 14:51:09 by williamcapt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ptrc;

	ptr = (unsigned char *)s;
	ptrc = (unsigned char)c;
	while (n > 0)
	{
		if (ptrc != *(ptr))
		{
			ptr++;
			n--;
		}
		else
			return ((unsigned char *)ptr);
	}
	return (NULL);
}
