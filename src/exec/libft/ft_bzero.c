/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: williamcapt <williamcapt@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:36:28 by apiscopo          #+#    #+#             */
/*   Updated: 2025/02/06 14:49:26 by williamcapt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*char_s;

	if (n == 0)
		return ;
	char_s = (char *)s;
	while (n--)
	{
		*char_s++ = '\0';
	}
}
/*int main()
{
  const char a[] = "Burger";
  ft_bzero(a,3);
}*/
