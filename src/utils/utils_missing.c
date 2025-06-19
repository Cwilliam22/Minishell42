/* Fonctions utilitaires manquantes pour compiler le parser */
#include "minishell.h"

/* Assignment utilities */
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
	
	assign->next = NULL;
	return (assign);
}

void	add_assignment(t_assignment **head, t_assignment *new_assign)
{
	t_assignment	*current;
	
	if (!head || !new_assign)
		return;
	
	if (!*head)
	{
		*head = new_assign;
		return;
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



/* Error utilities */
void	print_syntax_error(char *token)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
}

void	print_error(char *cmd, char *arg, char *msg)
{
	printf("minishell: ");
	if (cmd)
		printf("%s: ", cmd);
	if (arg)
		printf("%s: ", arg);
	if (msg)
		printf("%s", msg);
	printf("\n");
}