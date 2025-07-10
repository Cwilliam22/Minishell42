/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:22:12 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/10 06:20:50 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->env[i])
	{
		free(exec->env[i][0]);
		free(exec->env[i][1]);
		free(exec->env[i]);
		i++;
	}
	free(exec->env);
	exec->env = NULL;
}

int	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (1);
}

int	free_var(t_exec *exec)
{
	if (!exec->path || !exec->cmd)
	{
		return (0);
	}
	free(exec->path);
	exec->path = NULL;
	free(exec->cmd);
	exec->cmd = NULL;
	return (1);
}

int	free_all_env(t_exec *exec)
{
	if (!exec->env)
		return (0);
	free_env(exec);
	return (1);
}

int	free_pipes(int **pipes, t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->nbr_pipes)
	{
		free(pipes[i]);
		i++;
	}
	return (0);
}

void	free_temp_env(char ***temp, int max_i)
{
	int	i;

	if (!temp)
		return ;
	i = 0;
	while (i < max_i && temp[i])
	{
		free_array(temp[i]);
		i++;
	}
	free(temp);
}
