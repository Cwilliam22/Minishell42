/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/20 09:23:17 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/15 15:00:22 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	checks for an alphanumeric character; it is equivalent to (isalpha(c)
	|| isdigit(c)).

RETURN VALUE
	The values returned are nonzero if the character c falls into the tested
	class, and zero if not.
*/

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
