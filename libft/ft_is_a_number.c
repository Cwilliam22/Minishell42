/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_a_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:56:32 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/08 19:56:40 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_is_a_number(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg)
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit((int)arg[i]))
			return (0);
		i++;
	}
	return (1);
}
