/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_from_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:55:39 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/08 19:55:49 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup_from_index(const char *src, size_t n)
{
	size_t	len;
	size_t	i;
	char	*new_str;

	if (!src)
		return (NULL);
	len = 0;
	while (src[n + len])
		len++;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = src[n + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
