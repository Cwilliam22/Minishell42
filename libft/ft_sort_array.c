/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:25:40 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/08 19:58:39 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static void	ft_swap(char **sorted, int i, int j)
{
	char	*buf;

	buf = sorted[i];
	sorted[i] = sorted[j];
	sorted[j] = buf;
}

char	**ft_sort_array(char **array)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	len = ft_arraylen(array);
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(array[i], array[j]) > 0)
				ft_swap(array, i, j);
			j++;
		}
		i++;
	}
	return (array);
}
