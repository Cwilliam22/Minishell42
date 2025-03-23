/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:59:44 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/30 16:11:04 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	Applies the function ’f’ on each character of the string passed as
	argument, passing its index as first argument. Each character is passed by
	address to ’f’ to be modified if necessary.

PARAMETERS
	s: The string on which to iterate.
	f: The function to apply to each character.

RETURN VALUE
	NONE
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
