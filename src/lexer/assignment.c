/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:41:26 by alfavre           #+#    #+#             */
/*   Updated: 2025/07/09 23:51:51 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Create a new assignment (VAR=value)
 * @param key: Variable name
 * @param value: Value to assign
 * @return: Pointer to the created assignment or NULL on error
 */
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
 * Add a new assignment to the end of the linked list
 * @param head: Pointer to the head of the list
 * @param new_assign: New assignment to add
 */
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

/**
 * Free the linked list of assignments
 * @param assignments: Pointer to the head of the list
 */
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

/**
 * Check if the word is a valid assignment (VAR=value)
 * @param str: The word to check
 * @return: 1 if it is a valid assignment, 0 otherwise
 */
int	is_assignment_word(char *str)
{
	return (str && ft_strchr(str, '='));
}

/**
 * Split an assignment (VAR=value) into key and value
 * @param assignment: The assignment string to split
 * @param key: Pointer to store the key
 * @param value: Pointer to store the value
 * @return: 1 on success, 0 on failure
 */
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
