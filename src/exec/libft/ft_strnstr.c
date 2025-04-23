/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: williamcapt <williamcapt@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:35:34 by apiscopo          #+#    #+#             */
/*   Updated: 2025/02/06 14:53:10 by williamcapt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return ((char *) haystack + i);
		}
		i++;
		j = 0;
	}
	return (0);
}

/*
int main() {
    const char *haystack = "Bonjour le monde !";
    const char *needle1 = "monde";
    const char *needle2 = "salut";
    const char *needle3 = "";
    size_t len = 20; // Limite de recherche

    // Test 1
    char *result1 = ft_strnstr(haystack, needle1, len);
    if (result1) {
        printf("Test 1 : '%s' trouvé à la position : %ld\n",
		 needle1, result1 - haystack);
    } else {
        printf("Test 1 : '%s' non trouvé\n", needle1);
    }
    return 0;
}*/
