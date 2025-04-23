/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: williamcapt <williamcapt@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:05:18 by apiscopo          #+#    #+#             */
/*   Updated: 2025/02/06 14:51:23 by williamcapt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*tmpd;
	const unsigned char	*tmps;
	size_t				i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	tmpd = (unsigned char *)dst;
	tmps = (const unsigned char *)src;
	while (n > 0)
	{
		tmpd[i] = tmps[i];
		n--;
		i++;
	}
	return (dst);
}
