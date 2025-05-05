
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

int    identification(char **arg, t_exec *exec)
{
	if (its_a_builtin(arg, exec))
		return (1);
	else
	{
		execute_externe(arg, exec->env, exec);
		return (1);
	}
	return (0);
}

int	its_a_builtin(char **arg, t_exec *exec)
{
	int	i;

	i = 0;
		while (tab_link[i].builtin != NULL) 
		{
			if (ft_strcmp(arg[0], tab_link[i].builtin) == 0)
				return (tab_link[i].fonction(arg, exec));
			i++;
		}
		return (0);
}

int	execute_externe(char **args, char ***env, t_exec *exec)
{
	pid_t	pid;
	char	*path;
	int		status;
	char	**env_temp;

	pid = fork();
	if (pid == 0)
	{
		env_temp = set_my_fucking_error(exec->env, exec);
		if (!apply_path(exec))
			return (0);
		execve(path, args, env);
		
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (ft_printf("Erreur in Execution of externes CMDs\n"), 0);
	return (1);
}

char **set_my_fucking_error(char ***env, t_exec *exec)
{
	char **new_env;
	int	i;

	i = 0;
	new_env = malloc(sizeof(char *) * (exec->nbr_var_env + 1));
	while (exec->env[i])
	{
		exec->env[i][0] = ft_strjoin(exec->env[i][0], "=");
		new_env[i] = ft_strjoin(exec->env[i][0], exec->env[i][1]);
		i++;
	}
	return (new_env);
}
// creat a new function to set the error of char ***
// need env in the form char ** not ***  (next step)