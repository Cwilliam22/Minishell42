/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:42:02 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/16 18:30:32 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	make_a_bigger_env(t_exec *exec, char ***temp, int i)
{
	int	j;

	while (exec->env[i])
	{
		j = 0;
		temp[i] = malloc(sizeof(char *) * 3);
		if (!temp[i])
			return (free_temp_env(temp, i), -1);
		while (exec->env[i][j])
		{
			temp[i][j] = ft_strdup(exec->env[i][j]);
			if (!temp[i][j])
			{
				temp[i][j] = NULL;
				free_array(temp[i]);
				return (free_temp_env(temp, i), -1);
			}
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
	exec->nbr_var_env++;
	temp = malloc(sizeof(char **) * (exec->nbr_var_env + 1));
	if (!temp)
		return (exec->nbr_var_env--, 0);
	place = make_a_bigger_env(exec, temp, i);
	if (place == -1)
		return (exec->nbr_var_env--, 0);
	temp[place] = malloc(sizeof(char *) * 3);
	if (!temp[place])
		return (free_temp_env(temp, place), exec->nbr_var_env--, 0);
	temp[place][0] = ft_strdup(new_variable);
	temp[place][1] = ft_strdup(new_value);
	temp[place][2] = NULL;
	temp[place + 1] = NULL;
	if (!temp[place][0] || !temp[place][1])
	{
		free_array(temp[place]);
		temp[place] = NULL;
		return (free_temp_env(temp, place), exec->nbr_var_env--, 0);
	}
	free_env(exec);
	exec->env = temp;
	return (1);
}

int	replace_value_var_or_add(char *new_value, int i, char ***env, int is_append)
{
	char	*old_value;

	if (!new_value)
		return (0);
	if (!is_append)
	{
		free(env[i][1]);
		env[i][1] = ft_strdup(new_value);
		if (!env[i][1])
			return (0);
	}
	else
	{
		old_value = env[i][1];
		env[i][1] = ft_strjoin(old_value, new_value);
		free(old_value);
		if (!env[i][1])
			return (0);
	}
	return (1);
}

static int	process_assignment(t_shell *shell, t_assignment *assign)
{
	int	env_index;

	if (!is_a_valid_identifier(assign->key))
	{
		print_export_error(assign->key);
		return (1);
	}
	env_index = find_sth_in_env(assign->key, shell->exec->env);
	if (env_index == -1)
	{
		if (!new_var(assign->value, assign->key, shell->exec))
			return (1);
	}
	else
	{
		if (!replace_value_var_or_add(assign->value, env_index, 
				shell->exec->env, assign->is_append))
			return (1);
	}
	return (0);
}

static int	export_with_assignment(t_shell *shell)
{
	t_assignment	*head;
	int				error;

	head = shell->cmd_list->assignments;
	error = 0;
	while (head)
	{
		error |= process_assignment(shell, head);
		head = head->next;
	}
	return (error);
}

static int	export_args_only(t_shell *shell)
{
	char	**arg;
	int		i;
	int		error;

	arg = shell->cmd_list->args;
	error = 0;
	i = 1;
	while (arg[i])
	{
		if (ft_strchr(arg[i], '='))
		{
			i++;
			continue ;
		}
		if (!is_a_valid_identifier(arg[i]))
		{
			print_export_error(arg[i]);
			error = 1;
			i++;
			return (error);
		}
		else if (find_sth_in_env(arg[i], shell->exec->env) == -1)
		{
			if (!new_var("", arg[i], shell->exec))
				error = 1;
		}
		i++;
	}
	return (error);
}

int	builtin_export(t_shell *shell)
{
	int	error;

	error = 0;
	if (shell->exec->nbr_arg == 1)
	{
		if (print_env_sorted(shell->exec))
			return (0);
		else
			return (1);
	}
	if (shell->cmd_list->assignments)
		error |= export_with_assignment(shell);
	if (shell->exec->nbr_arg > 1)
		error |= export_args_only(shell);
	return (error);
}
