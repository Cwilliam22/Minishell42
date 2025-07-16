/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:42:25 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/16 12:21:39 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(t_exec *exec)
{
	exec->cmd_path = NULL;
	exec->path = NULL;
	exec->nbr_process = 0;
	exec->nbr_pipes = 0;
	exec->nbr_var_env = 0;
	exec->nbr_arg = 0;
	exec->cmd = NULL;
	exec->out = 0;
	exec->oldpwd = NULL;
	exec->pwd = NULL;
	exec->is_pipe = 0;
	exec->abs_path = 0;
	exec->rel_path = 0;
	exec->exit = 0;
}
/*

t_command	*create_test_command(void)
{
	t_command	*cmd1 = malloc(sizeof(t_command));
	t_command	*cmd2 = malloc(sizeof(t_command));

	// cmd1 echo test
	cmd1->name = ft_strdup("echo");
	cmd1->args = malloc(sizeof(char *) * 3);
	cmd1->args[0] = ft_strdup("echo");
	cmd1->args[1] = ft_strdup("test");
	cmd1->args[2] = NULL;
	cmd1->redirections = NULL;
	cmd1->next = cmd2;

	// cmd2 : wc -l
	cmd2->name = ft_strdup("wc");
	cmd2->args = malloc(sizeof(char *) * 3);
	cmd2->args[0] = ft_strdup("wc");
	cmd2->args[1] = ft_strdup("-l");
	cmd2->args[2] = NULL;
	cmd2->redirections = NULL;
	cmd2->next = NULL;

	return cmd1;
}


t_command	*create_test_command(void)
{
	t_command	*cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);

	cmd->name = ft_strdup("ls");
	cmd->args = malloc(sizeof(char *) * 2);
	if (!cmd->args)
		return (NULL);

	cmd->args[0] = ft_strdup("ls");
	cmd->args[1] = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;

	return cmd;
}


void	init_all(t_exec *exec)
{
	exec->env = NULL;
	exec->cmd_path = NULL;
	exec->path = NULL;
	exec->fd_in = 0;
	exec->fd_out = 0;
	exec->nbr_process = 0;
	exec->nbr_pipes = 0;
	exec->nbr_var_env = 0;
	exec->nbr_arg = 0;
	exec->cmd = NULL;
	exec->out = 0;
	exec->is_pipe = 0;
}


int	main(int argc, char **argv, char **envp)
{
	t_exec exec;

	(void)argc;
	(void)argv;
	t_command *cmd_list = create_test_command();
	init_all(&exec);
	if (!copy_env1(envp, &exec))
		return (1);
	if (!exec.env)
		return (1);
	exec.nbr_var_env = ft_envlen(exec.env);
	exec.nbr_process = ft_lstlen(cmd_list);
	exec.nbr_pipes = exec.nbr_process - 1;
	exec.path = ft_strdup(exec.env[find_var_path(exec.env)][1]);
	if (exec.nbr_process == 1)
	{
		if (!identification(cmd_list, &exec))
			return (ft_printf("Not a command valid\n"), 1);
	}
	else if (exec.nbr_process > 1)
	{
		if (!pipeline(cmd_list, &exec))
			return (ft_printf("Not a command valid\n"), 1);
	}
	free_var(&exec);
	free_all_env(&exec);
	return (0);
}
*/

static int	check_args(t_shell *shell)
{
	char	**process;

	if (!shell || !shell->cmd_list || !shell->cmd_list->args)
		return (ft_printf("Error: Shell or command list is NULL\n"), 1);
	process = shell->cmd_list->args;
	if (!process || !process[0] || !process[0][0] || is_all_spaces(process[0]))
	{
		if (process[0] && process[0][0] == '\0')
			printf("Command '%s' not found\n", process[0]);
		else if (is_all_spaces(process[0]))
			printf("%s: command not found\n", process[0]);
		exit_codes(shell, 127, NULL);
		return (0);
	}
	return (1);
}

void	init_exec(t_shell *shell)
{
	if (shell->exec->oldpwd)
	{
		free(shell->exec->oldpwd);
		shell->exec->oldpwd = NULL;
	}
	if (shell->exec->pwd)
	{
		free(shell->exec->pwd);
		shell->exec->pwd = NULL;
	}
	shell->exec->oldpwd = getcwd(NULL, 0);
	shell->exec->pwd = getcwd(NULL, 0);
	shell->exec->nbr_var_env = ft_envlen(shell->exec->env);
	shell->exec->nbr_process = ft_lstlen(shell->cmd_list);
	shell->exec->nbr_pipes = shell->exec->nbr_process - 1;
}

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	free(exec->cmd_path);
	free(exec->path);
	free(exec->oldpwd);
	free(exec->pwd);
	if (exec->env)
		free_all_env(exec);
}

void	var_path(t_shell *shell)
{
	int			path_index;
	static int	call_count = 0;

	call_count++;
	if (shell->exec->path)
	{
		free(shell->exec->path);
		shell->exec->path = NULL;
	}
	path_index = find_var_path(shell->exec->env);
	if (path_index >= 0)
		shell->exec->path = ft_strdup(shell->exec->env[path_index][1]);
	else
		shell->exec->path = NULL;
}

int	ft_exec(t_shell *shell)
{
	int	exec_result;

	if (g_signal_received == SIGINT)
	{
		exit_codes(shell, 130, NULL);
		return (130);
	}
	init_all(shell->exec);
	init_exec(shell);
	var_path(shell);
	if (g_signal_received == SIGINT)
	{
		exit_codes(shell, 130, NULL);
		return (130);
	}
	if (shell->exec->nbr_process == 1)
	{
		if (its_absolute_path(shell))
			shell->exec->abs_path = 1;
		if (its_relative_path(shell))
			shell->exec->rel_path = 1;
		shell->exec->is_pipe = 0;
		if (check_args(shell))
		{
			exec_result = identification(shell);
			if (exec_result == 0)
				exec_result = shell->exec->out;
		}
		else
			exec_result = shell->exec->out;
	}
	else if (shell->exec->nbr_process > 1)
	{
		shell->exec->is_pipe = 1;
		if (!pipeline(shell))
		{
			ft_printf("Not a command valid\n");
			exec_result = 1;
		}
		else
			exec_result = shell->exec->out;
	}
	else
		exec_result = shell->exec->out;
	handle_signal(shell);
	free_var(shell->exec);
	return (exec_result);
}
