/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: williamcapt <williamcapt@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:38:18 by apiscopo          #+#    #+#             */
/*   Updated: 2025/02/06 14:51:28 by williamcapt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*tmpd;
	unsigned const char	*tmps;
	size_t				i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	tmpd = (unsigned char *)dst;
	tmps = (unsigned const char *)src;
	if (tmpd > tmps)
	{
		while (len-- > 0)
			tmpd[len] = tmps[len];
	}
	else
	{
		while (i < len)
		{
			tmpd[i] = tmps[i];
			i++;
		}
	}
	return (dst);
}
/*
Hello World
HelHello Wo
*/
