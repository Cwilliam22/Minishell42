/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:09:18 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/31 09:52:56 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Outputs the integer ’n’ to the given file descriptor.

PARAMETERS
	n: The integer to output.
	fd: The file descriptor on which to write.

RETURN VALUE
	NONE
*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	i;

	if (n < 0)
	{
		i = (-n);
		ft_putchar_fd('-', fd);
	}
	else
		i = n;
	if (i >= 10)
	{
		ft_putnbr_fd(i / 10, fd);
		ft_putnbr_fd(i % 10, fd);
	}
	if (i < 10)
		ft_putchar_fd((i % 10) + '0', fd);
}
