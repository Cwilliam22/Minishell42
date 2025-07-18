/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:38:16 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/10 05:59:56 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_allocations(char ***temp, int i, int size)
{
	temp[i] = malloc(sizeof(char *) * size);
	if (!temp[i])
		return (0);
	return (1);
}

int	copy_strings_in_env(t_exec *exec, int m, char ***temp, int i)
{
	int	j;
	int	k;

	j = 0;
	if (!malloc_allocations(temp, i, 3))
		return (0);
	while (exec->env[m][j])
	{
		temp[i][j] = ft_strdup(exec->env[m][j]);
		if (!temp[i][j])
		{
			k = 0;
			while (k < j)
				free(temp[i][k++]);
			free(temp[i]);
			return (0);
		}
		j++;
	}
	temp[i][j] = NULL;
	return (1);
}

int	make_a_new_env(t_exec *exec, int index, char ***temp, int i)
{
	int		m;

	m = 0;
	while (exec->env[m])
	{
		if (m == index)
		{
			m++;
			continue ;
		}
		if (!copy_strings_in_env(exec, m, temp, i))
		{
			free_temp_env(temp, i);
			return (0);
		}
		i++;
		m++;
	}
	temp[i] = NULL;
	return (1);
}

int	unset_var(int index, t_exec *exec)
{
	char	***temp;
	int		i;

	i = 0;
	exec->nbr_var_env--;
	temp = malloc(sizeof(char **) * (exec->nbr_var_env + 1));
	if (!temp)
	{
		exec->nbr_var_env++;
		return (0);
	}
	if (!make_a_new_env(exec, index, temp, i))
	{
		exec->nbr_var_env++;
		return (0);
	}
	free_env(exec);
	exec->env = temp;
	return (1);
}

int	builtin_unset(t_shell *shell)
{
	int		i;
	int		place;
	char	**arg;
	t_exec	*exec;

	i = 0;
	arg = shell->cmd_list->args;
	exec = shell->exec;
	if (exec->nbr_arg == 1)
		return (0);
	while (arg[i])
	{
		place = find_sth_in_env(arg[i], exec->env);
		if (place != -1)
			unset_var(place, exec);
		i++;
	}
	return (0);
}
