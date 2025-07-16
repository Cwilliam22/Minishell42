/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:22:11 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/16 14:11:05 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_in_path(t_shell *shell, char **paths, int flag)
{
	int		i;
	char	*test_path;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		test_path = ft_strjoin(tmp, shell->exec->cmd);
		free(tmp);
		if (access(test_path, flag) == 0)
		{
			shell->exec->cmd_path = test_path;
			free_array(paths);
			return (1);
		}
		free(test_path);
		i++;
	}
	free_array(paths);
	return (0);
}

int	command_exist(t_shell *shell)
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
	if (find_in_path(shell, paths, F_OK))
		return (1);
	return (exit_codes(shell, 127, NULL), 0);
}
