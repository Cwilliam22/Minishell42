/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:22:12 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/02 18:22:14 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_env(char ***env)
{
	int	i;
	int	j;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			free(env[i][j]);
			j++;
		}
		free(env[i]);
		i++;
	}
	free(env);
	env = NULL;
	return (1);
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
	free(exec->cmd);
	return (1);
}

int	free_all_env(t_exec *exec)
{
	if (!exec->env)
		return (0);
	free_env(exec->env);
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
