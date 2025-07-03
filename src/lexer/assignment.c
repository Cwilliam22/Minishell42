/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:41:26 by alfavre           #+#    #+#             */
/*   Updated: 2025/07/03 15:13:34 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_assignment	*create_assignment(char *key, char *value)
{
	t_assignment	*assign;

	assign = malloc(sizeof(t_assignment));
	if (!assign)
		return (NULL);
	assign->key = ft_strdup(key);
	if (!assign->key)
	{
		free(assign);
		return (NULL);
	}
	assign->value = ft_strdup(value);
	if (!assign->value)
	{
		free(assign->key);
		free(assign);
		return (NULL);
	}
	assign->is_append = 0;
	assign->next = NULL;
	return (assign);
}

/**
 * Create an append assignment (VAR+=value)
 * @param key: Variable name
 * @param value: Value to append
 * @return: Pointer to the created assignment or NULL on error
 */
t_assignment *create_append_assignment(char *key, char *value)
{
    t_assignment *assign;
    
    assign = malloc(sizeof(t_assignment));
    if (!assign)
        return (NULL);
    
    assign->key = ft_strdup(key);
    if (!assign->key)
    {
        free(assign);
        return (NULL);
    }
    
    assign->value = ft_strdup(value);
    if (!assign->value)
    {
        free(assign->key);
        free(assign);
        return (NULL);
    }
    
    assign->is_append = 1;  // Marque cet assignement comme append
    assign->next = NULL;
    return (assign);
}

void	add_assignment(t_assignment **head, t_assignment *new_assign)
{
	t_assignment	*current;

	if (!head || !new_assign)
		return ;
	if (!*head)
	{
		*head = new_assign;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_assign;
}

void	free_assignments(t_assignment *assignments)
{
	t_assignment	*current;
	t_assignment	*next;

	current = assignments;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

int	is_assignment_word(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (str[i] == '=' && i > 0);
}

/**
 * Check if the word is an append assignment (VAR+=value)
 * @param word: The word to check
 * @return: 1 if it is an append assignment, 0 otherwise
 */
int is_append_assignment_word(const char *word)
{
    int i;
    
    if (!word || !*word)
        return (0);
    
    // First character must be a letter or underscore
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
int split_append_assignment(const char *assignment, char **key, char **value)
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

int	split_assignment(char *assignment, char **key, char **value)
{
	char	*equal_pos;
	size_t	key_len;

	if (!assignment || !key || !value)
		return (0);
	equal_pos = ft_strchr(assignment, '=');
	if (!equal_pos)
		return (0);
	key_len = equal_pos - assignment;
	*key = ft_substr(assignment, 0, key_len);
	if (!*key)
		return (0);
	*value = ft_strdup(equal_pos + 1);
	if (!*value)
	{
		free(*key);
		*key = NULL;
		return (0);
	}
	return (1);
}
