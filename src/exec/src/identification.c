
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

int    identification(char ***arg, t_exec *exec, int line)
{
	char **cmd;
	int i;

	i = 0;
	cmd = malloc(sizeof(char *) * (ft_tablen_2d(arg[line]) + 1));
	exec->cmd = ft_strdup(arg[line][0]);
	while (arg[line][i])
	{
		cmd[i] = ft_strdup(arg[line][i]);
		i++;
	}
	cmd[i] = NULL;
	if (its_a_builtin(cmd, exec))
		return (1);
	else
	{
		printf("C'est une commande externe\n");
		execute_externe(cmd, exec->env, exec);
		return (1);
	}
	// free la variable cmd 
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


void	print_char_double(char **tab)
{
	int i = 0;

	while (tab && tab[i])
	{
		printf("tab[%d] = %s\n", i, tab[i]);
		i++;
	}
}


int	execute_externe(char **args, char ***env, t_exec *exec)
{
	pid_t	pid;
	int		status;
	char	**env_temp;

	(void)env;
	pid = fork();
	if (pid == 0)
	{
		env_temp = set_my_fucking_error(exec);
		if (!apply_path(exec))
			return (0);
		execve(exec->cmd_path, args, env_temp);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		return (ft_printf("Erreur in Execution of externes CMDs\n"), 0);
	return (1);
}

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

