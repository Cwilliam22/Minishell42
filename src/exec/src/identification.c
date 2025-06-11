
#include "../../../include/exec.h"

t_builtin tab_link[] = {
	{"cd", builtin_cd},
	{"echo", builtin_echo},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{NULL, NULL}};

int    identification(t_command *current_cmd, t_exec *exec)
{
	char **process;

	process = current_cmd->args;
	exec->cmd = ft_strdup(current_cmd->name);
	if (its_a_builtin(process, exec))
	{
		return (1);
	}
	else
	{
		execute_externe(process, exec);
		return (1);
	}
	return (0);
}

int	its_a_builtin(char **arg, t_exec *exec)
{
	int	i;

	i = 0;
	exec->nbr_arg = ft_tablen_2d(arg);
	while (tab_link[i].builtin != NULL) 
	{
		if (ft_strcmp(arg[0], tab_link[i].builtin) == 0)
			return (tab_link[i].fonction(arg, exec));
		i++;
	}
	return (0);
}

int	execute_externe(char **args, t_exec *exec)
{
	pid_t	pid;
	int		status;
	char	**env_temp;

	pid = fork();
	if (pid == 0)
	{
		env_temp = set_my_fucking_error(exec);
		if (!apply_path(exec))
			return (0);
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

	i = 0;
	new_env = malloc(sizeof(char *) * (exec->nbr_var_env + 1));
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

