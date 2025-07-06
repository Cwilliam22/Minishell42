/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_assignment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:25:11 by alexis            #+#    #+#             */
/*   Updated: 2025/07/04 14:26:25 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Create an append assignment (VAR+=value)
 * @param key: Variable name
 * @param value: Value to append
 * @return: Pointer to the created assignment or NULL on error
 */
t_assignment	*create_append_assignment(char *key, char *value)
{
	t_assignment	*assign;

	assign = malloc(sizeof(t_assignment));
	if (!assign)
		return (NULL);
	assign->key = ft_strdup(key);
	if (!assign->key)
		return (free(assign), NULL);
	assign->value = ft_strdup(value);
	if (!assign->value)
		return (free(assign->key), free(assign), NULL);
	assign->is_append = 1;
	assign->next = NULL;
	return (assign);
}

/**
 * Check if the word is an append assignment (VAR+=value)
 * The first character must be a letter or underscore
 * @param word: The word to check
 * @return: 1 if it is an append assignment, 0 otherwise
 */
int	is_append_assignment_word(const char *word)
{
	int	i;

	if (!word || !*word)
		return (0);
	if (!ft_isalpha(word[0]) && word[0] != '_')
		return (0);
	i = 1;
	while (word[i] && !(word[i] == '+' && word[i + 1] == '='))
	{
		if (!ft_isalnum(word[i]) && word[i] != '_')
			return (0);
		i++;
	}
	return (word[i] == '+' && word[i + 1] == '=');
}

/**
 * Split an append assignment (VAR+=value) into key and value
 * @param assignment: The assignment string to split
 * @param key: Pointer to store the key
 * @param value: Pointer to store the value
 * @return: 1 on success, 0 on failure
 */
int	split_append_assignment(const char *assignment, char **key, char **value)
{
	char	*plus_pos;
	int		key_len;

	plus_pos = ft_strnstr(assignment, "+=", ft_strlen(assignment));
	if (!plus_pos)
		return (0);
	key_len = plus_pos - assignment;
	*key = ft_substr(assignment, 0, key_len);
	if (!*key)
		return (0);
	*value = ft_strdup(plus_pos + 2);
	if (!*value)
	{
		free(*key);
		*key = NULL;
		return (0);
	}
	return (1);
}
