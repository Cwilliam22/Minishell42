/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:44:01 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/12 18:28:42 by alexis           ###   ########.fr       */
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
			return (exit_code);
		}
		i++;
	}
	return (127);
}

int	check_file_before_exec(char *path, char *cmd_name)
{
	struct stat st;

	if (stat(path, &st) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (126);
	}
	if (!(st.st_mode & S_IXUSR))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	return (0);
}

// Ajoutez du debug dans execute_externe :
int	execute_externe(char **args, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	**env_temp;
	t_exec	*exec;

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
	pid = fork();
	if (pid == 0)
	{
		int check_result = check_file_before_exec(exec->cmd_path, args[0]);
		if (check_result != 0)
			exit(check_result);
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
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	else
		return (perror("fork failed"), 1);
	return (1);
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
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	process = shell->cmd_list->args;
	apply_redir_result = apply_redirections(shell->cmd_list->redirections);
	shell->exec->cmd = ft_strdup(shell->cmd_list->args[0]);
	if (!shell->exec->cmd)
		return (clear_std(saved_stdout, saved_stdin), 0);
	if (apply_redir_result != 0)
	{
		clear_std(saved_stdout, saved_stdin);
		exit_codes(shell, apply_redir_result, "");
		if (shell->exec->nbr_process > 1)
			exit(apply_redir_result);
		return (apply_redir_result);
	}
	if (is_builtin(shell->cmd_list->args[0]))
		exit_code = execute_builtin(shell);
	else
		exit_code = execute_externe(process, shell);
	clear_std(saved_stdout, saved_stdin);
	exit_codes(shell, exit_code, "");
	if (shell->exec->nbr_process > 1)
		exit(exit_code);
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
