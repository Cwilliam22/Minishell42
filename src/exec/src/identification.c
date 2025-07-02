
#include "minishell.h"

static void	clear_std(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

int	identification(t_shell *shell)
{
	char	**process;
	int		apply_redir_result;
	int		saved_stdout;
	int		saved_stdin;

	if (!shell || !shell->cmd_list || !shell->exec)
		return (ft_printf("Error: Shell or command list is NULL\n"), 0);
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	process = shell->cmd_list->args;
	apply_redir_result = apply_redirections(shell->cmd_list->redirections);
	shell->exec->cmd = ft_strdup(shell->cmd_list->args[0]);
	if (!process || !process[0] || process[0][0] == '\0'
		|| is_all_spaces(process[0]))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		if (process && process[0])
			ft_putstr_fd(process[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	shell->exec->cmd = ft_strdup( shell->cmd_list->args[0]);
	if (!shell->exec->cmd)
			return (clear_std(saved_stdout, saved_stdin), 0);
	if (apply_redir_result == EXIT_SIGINT
		|| apply_redir_result == GENERAL_ERROR)
		return (clear_std(saved_stdout, saved_stdin), apply_redir_result);
	if (its_a_builtin(shell))
		return (clear_std(saved_stdout, saved_stdin), 1);
	else
		return (execute_externe(process, shell),
			clear_std(saved_stdout, saved_stdin), 1);
	clear_std(saved_stdout, saved_stdin);
	return (0);
}

int	its_a_builtin(t_shell *shell)
{
	int	i;
	t_builtin tab_link[] = {
	{"cd", builtin_cd},
	{"echo", builtin_echo},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{NULL, NULL}};

	i = 0;
	shell->exec->nbr_arg = ft_tablen_2d(shell->cmd_list->args);
	while (tab_link[i].builtin != NULL) 
	{
		if (ft_strcmp(shell->cmd_list->args[0], tab_link[i].builtin) == 0)
			return (tab_link[i].fonction(shell));
		i++;
	}
	return (0);
}

int	execute_externe(char **args, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	**env_temp;
	t_exec *exec;

	exec = shell->exec;
	pid = fork();
	if (pid == 0)
	{
		env_temp = set_my_fucking_error(exec);
		if (!shell->exec->abs_path && !shell->exec->rel_path)
		{
			if (!apply_path(shell))
				return (0);
		}
		// free env_temp à la fin ??
		execve(exec->cmd_path, args, env_temp);
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (ft_printf("Erreur in Execution of externes CMDs\n"), 0);
	return (1);
}

// Pas free env_temp 

char **set_my_fucking_error(t_exec *exec)
{
	char **new_env;
	int	i;
	int len;

	i = 0;
	len = ft_envlen(exec->env);
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	while (exec->env[i])
	{
		char *temp = ft_strjoin(exec->env[i][0], "=");
		new_env[i] = ft_strjoin(temp, exec->env[i][1]);
		free(temp);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

