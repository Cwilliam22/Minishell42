/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:17:34 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/03 16:20:54 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_var_path(char ***env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] && env[i][1] && ft_strcmp(env[i][0], "PATH") == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*read_in_path(char ***env, int place)
{
	char	*src;
	char	*path;
	int		i;

	if (!env[place] || !env[place][1])
		return (NULL);
	src = env[place][1];
	i = 0;
	while (src[i])
		i++;
	path = malloc(sizeof(char) * (i + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (src[i])
	{
		path[i] = src[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

int	apply_path(t_shell *shell)
{
	char	**paths;
	char	*test_path;
	char	*tmp;
	int		i;

	paths = ft_split(read_in_path(shell->exec->env,
				find_var_path(shell->exec->env)), ':');
	if (!paths || !paths[0])
	{
		free_array(paths);
		shell->exec->cmd_path = NULL;
		return (ft_printf("No PATH variable found!\n"), 0);
	}
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		test_path = ft_strjoin(tmp, shell->exec->cmd);
		free(tmp);
		if (access(test_path, X_OK) == 0)
		{
			shell->exec->cmd_path = test_path;
			free_array(paths);
			return (1);
		}
		free(test_path);
		i++;
	}
	free_array(paths);
	return (exit_codes(shell, 127, NULL), 0);
}

int	its_absolute_path(t_shell *shell)
{
	if (shell->cmd_list->args[0][0] == '/')
		shell->exec->cmd_path = ft_strdup(shell->cmd_list->args[0]);
	if (!shell->exec->cmd_path)
		return (0);
	return (1);
}

int	its_relative_path(t_shell *shell)
{
	if (shell->cmd_list->args[0][0] == '.'
		&& shell->cmd_list->args[0][1] == '/')
		shell->exec->cmd_path = ft_strdup(shell->cmd_list->args[0]);
	if (!shell->exec->cmd_path)
		return (0);
	return (1);
}
