/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:42:02 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/03 13:52:37 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_a_bigger_env(t_exec *exec, char ***temp, int i, int j)
{
	while (exec->env[i])
	{
		j = 0;
		if (!malloc_allocations(temp, i, 3))
			return (free_env(temp), 0);
		while (exec->env[i][j])
		{
			temp[i][j] = ft_strdup(exec->env[i][j]);
			j++;
		}
		temp[i][j] = NULL;
		i++;
	}
	return (1);
}

int	new_var(char *new_value, char *new_variable, t_exec *exec)
{
	char	***temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	exec->nbr_var_env++;
	temp = malloc(sizeof(char **) * (exec->nbr_var_env + 1));
	if (!temp)
		return (0);
	if (!make_a_bigger_env(exec, temp, i, j))
		return (free_env(temp), 0);
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

int	replace_value_var(char *new_value, int i, char ***env)
{
	free(env[i][1]);
	env[i][1] = ft_strdup(new_value);
	if (!env[i][1])
		return (0);
	return (1);
}


int	builtin_export(t_shell *shell)
{
	int		i;
	char	*new_value;
	char	*new_variable;
	char	**arg;
	t_exec	*exec;

	new_value = NULL;
	new_variable = NULL;
	exec = shell->exec;
	arg = shell->cmd_list->args;
	while ()
	{
		if (exec->nbr_arg == 1)
		{
			if (!print_env_sorted(exec))
				return (exit_codes(shell, SUCCESS, ""), 0);
		}
		else if (exec->nbr_arg > 1)
		{
			i = find_sth_in_env(arg[1], exec->env);
			if (i == -1)
			{
				if (!new_var(new_value, new_variable, exec))
					return (exit_codes(shell, SUCCESS, ""), 0);
			}
			else if (!replace_value_var(new_value, i, exec->env))
				return (exit_codes(shell, SUCCESS, ""), 0);
		}
		if (new_value != NULL || new_variable != NULL)
		{
			free(new_value);
			free(new_variable);
		}
	}
	return (1);
}
