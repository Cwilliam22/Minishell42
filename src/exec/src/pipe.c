/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:17:24 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/02 18:17:26 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline(t_shell *shell)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * shell->exec->nbr_pipes);
	while (i < shell->exec->nbr_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
	if (!execute_pipeline(shell, pipes))
		return (ft_printf("Error in execute pipeline\n"), 0);
	return (1);
}

int	execute_pipeline(t_shell *shell, int **pipes)
{
	pid_t	*pids;
	int		i;
	int		status;

	i = 0;
	pids = malloc(sizeof(pid_t) * shell->exec->nbr_process);
	if (!pids)
		return (ft_printf("Error malloc pids\n"), 0);
	while (i < shell->exec->nbr_process && shell->cmd_list)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i == 0)
				dup2(pipes[i][1], STDOUT_FILENO);
			else if (i < shell->exec->nbr_process - 1)
			{
				dup2(pipes[i - 1][0], STDIN_FILENO);
				dup2(pipes[i][1], STDOUT_FILENO);
			}
			else
				dup2(pipes[i - 1][0], STDIN_FILENO);
			close_pipes(pipes, shell->exec);
			if (!identification(shell))
				exit(1);
			exit(0);
		}
		else if (pids[i] < 0)
			return (ft_printf("Error in fork\n"), 0);
		shell->cmd_list = shell->cmd_list->next;
		i++;
	}
	close_pipes(pipes, shell->exec);
	i = 0;
	while (i < shell->exec->nbr_process)
	{
		if (pids[i] > 0)
			waitpid(pids[i], &status, 0);
		i++;
	}
	free_pipes(pipes, shell->exec);
	free(pipes);
	free(pids);
	return (1);
}

int	close_pipes(int **pipes, t_exec *exec)
{
	int	j;

	j = 0;
	while (j < exec->nbr_process - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	return (1);
}

// exit(0) au cas ou il ne trouve pas la commande,
	// qu'il continue a executer le code dans le child 
// i == 0 (pas de stdin)
// i == nb_process - 1 (pas de stdout)
