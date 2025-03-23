/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:24:22 by alfavre           #+#    #+#             */
/*   Updated: 2025/03/16 14:56:15 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_nb_strings(const char *s, char c)
{
	size_t	nb_strings;
	size_t	i;

	if (!s[0])
		return (0);
	i = 0;
	nb_strings = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			nb_strings++;
		while (s[i] && !(s[i] == c))
			i++;
	}
	return (nb_strings);
}

static void	ft_get_next_string(char **tab, size_t *s_len, char c)
{
	size_t	i;

	i = 0;
	*tab += *s_len;
	*s_len = 0;
	while (**tab && **tab == c)
		(*tab)++;
	while ((*tab)[i])
	{
		if ((*tab)[i] == c)
			return ;
		(*s_len)++;
		i++;
	}
}

/**
* @brief Allocates (with malloc(3)) and returns an array of strings obtained by
* splitting ’s’ using the character ’c’ as a delimiter. The array must end
* with a NULL pointer.
* @param s The string to be split.
* @param c The delimiter character.
* @return The array of new strings resulting from the split. NULL if the
* allocation fails.
*/
char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*next_string;
	size_t	next_string_len;
	size_t	index;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_nb_strings(s, c) + 1));
	if (!tab)
		return (NULL);
	next_string = (char *)s;
	next_string_len = 0;
	index = 0;
	while (index < ft_nb_strings(s, c))
	{
		ft_get_next_string(&next_string, &next_string_len, c);
		tab[index] = malloc(sizeof(char) * (next_string_len + 1));
		if (!tab[index])
			return (ft_free(tab));
		ft_strlcpy(tab[index], next_string, next_string_len + 1);
		index++;
	}
	tab[index] = NULL;
	return (tab);
}
