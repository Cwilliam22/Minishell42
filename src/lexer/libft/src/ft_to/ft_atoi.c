/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:29:17 by alfavre           #+#    #+#             */
/*   Updated: 2024/12/29 14:08:14 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	The atoi() function converts the initial portion of the string pointed
	to by nptr to int. The behavior is the same as

		strtol(nptr, NULL, 10);

	except that atoi() does not detect errors.

RETURN VALUE
	The converted value or 0 on error.
*/

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	negatif;
	int	result;

	negatif = 1;
	result = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			negatif = -1;
		nptr++;
	}
	if (*nptr == '+' || *nptr == '-')
		return (0);
	while (*nptr)
	{
		if (*nptr >= 48 && *nptr <= 57)
			result = (10 * result) + (*nptr - 48);
		else
			break ;
		nptr++;
	}
	return (negatif * result);
}
