/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: williamcapt <williamcapt@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:19:24 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/06 14:52:59 by williamcapt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char				*res;
	unsigned int		i;

	i = 0;
	res = (char *)malloc((ft_strlen(s) + 1) * (sizeof(char)));
	if (!res)
		return (NULL);
	while (i < (unsigned int)ft_strlen(s))
	{
		res[i] = (f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
