/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:17:24 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/12 18:34:22 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_pipes(t_shell *shell, int ***pipes)
{
	int	i;

	i = 0;
	*pipes = malloc(sizeof(int *) * shell->exec->nbr_pipes);
	if (!*pipes)
		return (0);
	while (i < shell->exec->nbr_pipes)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i])
			return (free_pipes(*pipes, shell->exec), 0);
		if (pipe((*pipes)[i]) == -1)
			return (free_pipes(*pipes, shell->exec), 0);
		i++;
	}
	return (1);
}

static void	setup_child_pipes(int i, int **pipes, t_exec *exec)
{
	if (i == 0 && exec->nbr_process > 1)
	{
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	else if (i == exec->nbr_process - 1)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
	}
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
}

static int	exec_pipe(t_shell *shell, int **pipes, pid_t *pids)
{
	int		i;
	t_cmd	*current_cmd;

	i = 0;
	current_cmd = shell->cmd_list;
	while (i < shell->exec->nbr_process && current_cmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			// ✅ Dans les enfants, restaurer SIGPIPE par défaut
			signal(SIGPIPE, SIG_DFL);
			if (shell->exec->nbr_process > 1)
				setup_child_pipes(i, pipes, shell->exec);
			close_pipes(pipes, shell->exec);
			shell->cmd_list = current_cmd;
			if (!identification(shell))
				exit(127);
			exit(shell->exec->out);
		}
		else if (pids[i] < 0)
			return (ft_printf("Error in fork\n"), 0);
		current_cmd = current_cmd->next;
		i++;
	}
	return (1);
}

static int	wait_processes(pid_t *pids, t_exec *exec)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < exec->nbr_process)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			if (WIFSIGNALED(status))
			{
				int sig = WTERMSIG(status);
				if (sig == SIGPIPE)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd("Broken pipe\n", 2);
				}
			}
			else if (WIFEXITED(status))
			{
				int exit_code = WEXITSTATUS(status);
				// ✅ Détecter SIGPIPE encodé dans l'exit code
				if (exit_code == 141)  // 128 + 13 (SIGPIPE)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd("Broken pipe\n", 2);
				}
			}
			// Le statut final est celui du dernier processus de la pipeline
			if (i == exec->nbr_process - 1)
			{
				if (WIFEXITED(status))
					last_status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					last_status = 128 + WTERMSIG(status);
			}
		}
		i++;
	}
	return (last_status);
}

int	pipeline(t_shell *shell)
{
	int		**pipes;
	pid_t	*pids;
	int		exit_status;

	if (!create_pipes(shell, &pipes))
		return (ft_printf("Error creating pipes\n"), 0);
	pids = malloc(sizeof(pid_t) * shell->exec->nbr_process);
	if (!pids)
		return (free_pipes(pipes, shell->exec), 0);
	if (!exec_pipe(shell, pipes, pids))
		return (free(pids), free_pipes(pipes, shell->exec), 0);
	close_pipes(pipes, shell->exec);
	exit_status = wait_processes(pids, shell->exec);
	free_pipes(pipes, shell->exec);
	free(pipes);
	free(pids);
	exit_codes(shell, exit_status, NULL);
	return (1);
}
