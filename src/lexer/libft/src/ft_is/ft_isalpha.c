/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2008/10/20 10:46:56 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/30 17:28:51 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	checks  for an alphabetic character; in the standard "C" locale, it is
	equivalent to (isupper(c) || islower(c)).  In some locales, there  may
	be additional characters for which isalpha() is true—letters which are
	neither uppercase nor lowercase.

RETURN VALUE
	The values returned are nonzero if the character c falls into the tested
	class, and zero if not.
*/

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
