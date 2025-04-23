/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:06:16 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/10 16:45:26 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

ssize_t	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (s[i])
		ft_putchar(s[i++]);
	return (i);
}

/*
int main(void)
{
	char str[] = "Lausanne 42";
	ft_putstr(str); 
	return (0);
}
*/

// (l.23) Return 6 parce que (null) est composé de 6 caractère
// (l.27) nbr d'itération pour i = nbr de caractère de la string
