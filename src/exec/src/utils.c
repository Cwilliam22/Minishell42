/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:18:47 by wcapt             #+#    #+#             */
/*   Updated: 2025/03/22 15:32:05 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

char	*ft_strfchr(const char *s, int c)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	i--;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
