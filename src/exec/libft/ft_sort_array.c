/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <williamcapt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:25:40 by wcapt             #+#    #+#             */
/*   Updated: 2025/04/14 20:00:08 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char **ft_sort_array(char **array)
{
	char	*buf;
	char	**sorted;
	int		i;
    int		len;

	i = 0;
    len = ft_arraylen(array);
	sorted = malloc(sizeof(char *) * (len + 1));
	if (!sorted)
        return (NULL);
	while (i < len)
	{
		sorted[i] = ft_strdup(array[i]);
		i++;
	}
	sorted[i] = NULL;
	i = 1;
	while (i < len)
	{
		while (i < len - 1)
		{
			if (ft_strcmp(sorted[i], sorted[i + 1]) > 0)
			{
				buf = sorted[i + 1];
				sorted[i + 1] = sorted[i];
				sorted[i] = buf;
			}
			i++;
		}
		i = 1;
		len--;
	}
	return (sorted);
}