/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:52:33 by alexis            #+#    #+#             */
/*   Updated: 2025/07/08 21:54:36 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (n > len)
		n = len;
	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	ft_strncpy(dup, s, n);
	dup[n] = '\0';
	return (dup);
}
