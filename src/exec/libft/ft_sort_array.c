/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <williamcapt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:25:40 by wcapt             #+#    #+#             */
/*   Updated: 2025/04/10 15:29:26 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char **ft_sort_array(char **array)
{
	char *buf;
	int i;
    int len;

	i = 1;
    len = ft_arraylen(array);
	while (i < len)
	{
		while (i < len - 1)
		{
			if (ft_strcmp(array[i], array[i + 1]) > 0)
			{
				buf = array[i + 1];
				array[i + 1] = array[i];
				array[i] = buf;
			}
			i++;
		}
		i = 1;
		len--;
	}
	return (array);
}