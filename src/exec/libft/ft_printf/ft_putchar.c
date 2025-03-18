/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:06:30 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/10 16:45:05 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

ssize_t	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

/*
int main(void)
{
	char c = 'w';
	ft_putchar(c);
	return (0);
}
*/

// (l.18) Return 1 parce que 1 caractère imprimé
