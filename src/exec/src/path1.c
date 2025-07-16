/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:17:34 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/16 12:10:36 by alexis           ###   ########.fr       */
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

	if (g_signal_received == SIGINT)
	{
		exit_codes(shell, 130, NULL);
		return (0);
	}
	paths = ft_split(read_in_path(shell->exec->env,
				find_var_path(shell->exec->env)), ':');
	if (!paths || !paths[0])
	{
		free_array(paths);
		shell->exec->cmd_path = NULL;
		return (ft_printf("No PATH variable found!\n"), 0);
	}
	if (find_in_path(shell, paths, X_OK))
		return (1);
	return (exit_codes(shell, 127, NULL), 0);
}
