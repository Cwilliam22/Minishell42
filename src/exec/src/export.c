/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:42:02 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/09 15:42:54 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_a_bigger_env(t_exec *exec, char ***temp, int i)
{
	int	j;

	while (exec->env[i])
	{
		j = 0;
		if (!malloc_allocations(temp, i, 3))
			return (free_env(temp), -1);
		while (exec->env[i][j])
		{
			temp[i][j] = ft_strdup(exec->env[i][j]);
			j++;
		}
		temp[i][j] = NULL;
		i++;
	}
	return (i);
}

int	new_var(char *new_value, char *new_variable, t_exec *exec)
{
	char	***temp;
	int		i;
	int		place;

	i = 0;
	if (!is_a_valid_identifier(new_variable))
	{
		ft_putstr_fd("bash: export: `%s': not a valid identifier\n", 2);
		return (0);
	}
	exec->nbr_var_env++;
	temp = malloc(sizeof(char **) * (exec->nbr_var_env + 1));
	if (!temp)
		return (0);
	place = make_a_bigger_env(exec, temp, i);
	if (place == -1)
		return (free_env(temp), 0);
	i += place;
	temp[i] = malloc(sizeof(char *) * 3);
	if (!temp[i])
		return (0);
	temp[i][0] = ft_strdup(new_variable);
	temp[i][1] = ft_strdup(new_value);
	temp[i][2] = NULL;
	temp[i + 1] = NULL;
	if (!free_env(exec->env))
		return (0);
	exec->env = temp;
	return (1);
}

int	replace_value_var_or_add(char *new_value, int i, char ***env, int j)
{
	if (!j)
	{
		free(env[i][1]);
		env[i][1] = ft_strdup(new_value);
		if (!env[i][1])
			return (0);
	}
	else if (j)
	{
		env[i][1] = ft_strjoin(env[i][1], new_value);
		if (!env[i][1])
			return (0);
	}
	return (1);
}

int	export_with_assignment(t_shell *shell)
{
	t_assignment	*head;
	int				i;

	head = shell->cmd_list->assignments;
	while (head)
	{
		i = find_sth_in_env(head->key, shell->exec->env);
		if (i == -1)
		{
			if (!new_var(head->value, head->key, shell->exec))
				return (0);
		}
		else
		{
			if (!replace_value_var_or_add(head->value, i, shell->exec->env,
					head->is_append))
				return (0);
		}
		head = head->next;
	}
	return (1);
}

int	builtin_export(t_shell *shell)
{
	int				i;
	char			**arg;

	arg = shell->cmd_list->args;
	if (shell->exec->nbr_arg == 1)
	{
		if (!print_env_sorted(shell->exec))
			return (1);
	}
	i = 1;
	while (arg[i])
	{
		if (arg[i][0] == '=')
		{
			ft_putstr_fd("bash: export: `%s': not a valid identifier\n", 2);
			return (1);
		}
		if (ft_search_char(arg[i], '='))
		{
			if (!export_with_assignment(shell))
				return (1);
			i++;
			continue ;
		}
		if (!new_var("", arg[i], shell->exec))
			return (1);
		i++;
	}
	return (0);
}
