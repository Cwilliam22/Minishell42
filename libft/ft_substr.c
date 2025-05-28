/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: williamcapt <williamcapt@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:18:55 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/06 14:53:28 by williamcapt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			j;
	unsigned int	lens;
	char			*res;

	i = start;
	j = 0;
	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (start >= lens)
		return (ft_strdup(""));
	if (lens - start < len)
		len = lens - start;
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	while (j < len)
		res[j++] = s[i++];
	res[j] = '\0';
	return (res);
}
//l:27 On verifie que "start" ne soit pas supp ou égal a la len du string
//l:29 Ajuste len si nécessaire pour ne pas terminer en dehors de la string
//l:34 On copie "res" a partir de "j = 0" jusqu'a len en laissant + 1 pour
//le Null Terminated
