/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_a_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:56:32 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/09 21:41:37 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_is_a_number(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg)
		return (0);
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit((int)arg[i]))
			return (0);
		i++;
	}
	return (1);
}
