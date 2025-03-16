/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:59:23 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/30 17:28:59 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
    The bzero() function erases the data in the n bytes of the memory starting at
    the location pointed to by s, by writing zeros  (bytes  containing  '\0')  to
    that area.

    The  explicit_bzero() function performs the same task as bzero().  It differs
    from bzero() in that it guarantees that compiler optimizations will  not  re‐
    move  the  erase operation if the compiler deduces that the operation is "un‐
    necessary".

RETURN VALUE
	None
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
