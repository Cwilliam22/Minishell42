/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 03:09:38 by alfavre           #+#    #+#             */
/*   Updated: 2025/01/04 10:50:37 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strcmp() function compares the two strings s1 and s2. The locale
 * is not taken into account (for a  locale-aware  comparison, see strcoll(3)).
 * The comparison is done using unsigned characters.
 * 
 * strcmp() returns an integer indicating the result of the comparison, as
 * follows:
 * 
 * •  0, if the s1 and s2 are equal;
 * •  a negative value if s1 is less than s2;
 * •  a positive value if s1 is greater than s2.
 * 
 * The strncmp() function is similar, except it compares only  the  first  (at
 * most) n bytes of s1 and s2.
 * @param s1 string to compare with s2
 * @param s2 string to compare with s1
 * @param n number of characters to compare between s1 and s2
 * @return 	The strcmp() and strncmp() functions return an integer less than,
 * equal to, or greater than zero if s1 (or the first n bytes thereof) is found,
 * respectively, to be less than, to match, or be greater than s2.
 * 
 * The  sign  of a nonzero return value shall be determined by the sign
 * of the difference between the values of  the  first  pair  of  bytes
 * (both  interpreted as type unsigned char) that differ in the strings
 * being compared.
 * 
 * In glibc, as in most other implementations, the return value is the
 * arithmetic result of subtracting the last compared byte in s2 from the last
 * compared byte in s1. (If the two characters are equal, this difference is 0.)
 */
int	ft_strncmp(const char s1[], const char s2[], size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && (i < (n - 1)))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
