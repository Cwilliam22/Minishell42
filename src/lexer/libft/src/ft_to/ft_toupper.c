/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:30:50 by alfavre           #+#    #+#             */
/*   Updated: 2024/10/30 17:30:40 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	These functions convert lowercase letters to uppercase, and vice versa.

	If c is a lowercase letter, toupper() returns its uppercase equivalent, 
	if an uppercase representation exists in the current locale. Otherwise,
	it returns c. The toupper_l() function performs the same task, but uses the
	locale referred to by the locale handle locale.

	If c is an uppercase letter, tolower() returns its lowercase equivalent,
	if a lowercase representation exists in the current locale. Otherwise,
	it returns c. The tolower_l() function performs the same task, but uses the
	locale referred to by the locale handle locale.

	If c is neither an unsigned char value nor EOF, the behavior of these
	functions is undefined.

	The behavior of toupper_l() and tolower_l() is undefined if locale is the
	special locale object LC_GLOBAL_LOCALE (see duplocale(3)) or is not a valid
	locale object handle.

RETURN VALUE
	The value returned is that of the converted letter, or c if the conversion
	was not possible.
*/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
