/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:44:01 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/16 19:59:26 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_std(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

// Fonction pour vérifier si c'est un builtin (sans exécuter)
static int	is_builtin(char *cmd)
{
	char	*builtins[] = {
		"cd", "echo", "pwd", "export", "unset", "env", "exit", NULL
	};
	int		i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

// Fonction pour exécuter un builtin (retourne le bon exit code)
int	execute_builtin(t_shell *shell)
{
	int			i;
	int			exit_code;
	t_builtin	tab_link[] = {
		{"cd", builtin_cd},
		{"echo", builtin_echo},
		{"pwd", builtin_pwd},
		{"export", builtin_export},
		{"unset", builtin_unset},
		{"env", builtin_env},
		{"exit", builtin_exit},
		{NULL, NULL}
	};

	i = 0;
	shell->exec->nbr_arg = ft_tablen_2d(shell->cmd_list->args);
	while (tab_link[i].builtin != NULL)
	{
		if (ft_strcmp(shell->cmd_list->args[0], tab_link[i].builtin) == 0)
		{
			exit_code = tab_link[i].fonction(shell);
			//printf("Exit code: %d\n", exit_code);
			return (exit_code);
		}
		i++;
	}
	return (127);
}

// Ajoutez du debug dans execute_externe :
int	execute_externe(char **args, t_shell *shell)
{
	pid_t	pid;
	char	**env_temp;
	t_exec	*exec;

	int i = 0;
	while (args[i])
		i++;
	exec = shell->exec;
	if (!shell->exec->abs_path && !shell->exec->rel_path)
	{
		if (!command_exist(shell))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			return (127);
		}
	}
	if (shell->exec->nbr_process == 1)
		sig_core_dump_parent_signal();
	pid = fork();
	if (pid == 0)
	{
		child_signal();
		env_temp = set_my_fucking_error(exec);
		if (!shell->exec->abs_path && !shell->exec->rel_path)
		{
			if (!apply_path(shell))
				exit(127);
		}
		execve(exec->cmd_path, args, env_temp);
		perror("execve failed");
		exit(126);
	}
	else if (pid > 0)
	{
		if (shell->exec->nbr_process == 1)
		{
			int status;
			waitpid(pid, &status, 0);
			int real_exit_code = 0;
			if (WIFEXITED(status))
				real_exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				real_exit_code = 128 + WTERMSIG(status);
			parent_signal();
			return (real_exit_code);
		}
		else
			return (0);
	}
	else
		return (perror("fork failed"), 1);
	return (1);
}

int	execute_externe_pipeline(char **args, t_shell *shell)
{
	char	**env_temp;
	char	*cmd_path;

	if (!shell->exec->abs_path && !shell->exec->rel_path)
	{
		if (!command_exist(shell))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	cmd_path = shell->exec->cmd_path;
	if (!cmd_path)
		exit(127);
	extern char **environ;
	env_temp = environ;
	// Y a quoi dans env_temp ?
	execve(cmd_path, args, env_temp);
	perror("execve failed");
	exit(126);
}

int	identification(t_shell *shell)
{
	char	**process;
	int		apply_redir_result;
	int		saved_stdout;
	int		saved_stdin;
	int		exit_code;

	if (!shell || !shell->cmd_list || !shell->exec)
		return (ft_printf("Error: Shell or command list is NULL\n"), 0);
	if (g_signal_received == SIGINT)
	{
		exit_codes(shell, 130, "");
		if (shell->exec->nbr_process > 1)
			exit(130);
		return (130);
	}
	if (shell->exec->nbr_process > 1)
	{
		process = shell->cmd_list->args;
		shell->exec->cmd = ft_strdup(shell->cmd_list->args[0]);
		if (!shell->exec->cmd)
			exit(127);
		if (is_builtin(shell->cmd_list->args[0]))
			exit_code = execute_builtin(shell);
		else
			exit_code = execute_externe_pipeline(process, shell);
		exit(exit_code);
	}
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	process = shell->cmd_list->args;
	apply_redir_result = apply_redirections(shell->cmd_list->redirections, shell);
	shell->exec->cmd = ft_strdup(shell->cmd_list->args[0]);
	if (!shell->exec->cmd)
		return (clear_std(saved_stdout, saved_stdin), 0);
	if (apply_redir_result != 0)
	{
		clear_std(saved_stdout, saved_stdin);
		exit_codes(shell, apply_redir_result, "");
		return (apply_redir_result);
	}
	if (is_builtin(shell->cmd_list->args[0]))
	{
		exit_code = execute_builtin(shell);
		if (shell->exec->exit == 1)
			exit_code = shell->exec->out;
	}
	else
		exit_code = execute_externe(process, shell);
	clear_std(saved_stdout, saved_stdin);
	exit_codes(shell, exit_code, "");
	return (exit_code);
}

char	**set_my_fucking_error(t_exec *exec)
{
	char	**new_env;
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_envlen(exec->env);
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	while (exec->env[i])
	{
		temp = ft_strjoin(exec->env[i][0], "=");
		new_env[i] = ft_strjoin(temp, exec->env[i][1]);
		free(temp);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
