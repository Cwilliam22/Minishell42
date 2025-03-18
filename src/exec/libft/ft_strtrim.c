/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: williamcapt <williamcapt@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:21:02 by apiscopo          #+#    #+#             */
/*   Updated: 2025/02/06 14:53:22 by williamcapt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	new_len;
	char	*res;

	start = 0;
	end = ft_strlen(s1);
	if (!s1)
		return (NULL);
	while (start < end && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	new_len = end - start;
	res = (char *)malloc(end - start + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + start, new_len + 1);
	return (res);
}
