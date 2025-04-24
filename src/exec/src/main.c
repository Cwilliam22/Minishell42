
#include "../../../include/exec.h"

char *tab_arg[] = {"unset", "HOME", NULL}; 

void	init_all(t_exec *exec)
{
	exec->args = NULL;
	exec->env_sorted = NULL;
	exec->env = NULL;
	exec->cmd = NULL;
	exec->cmd_path = NULL;
	exec->path = NULL;
	exec->fd_in = 0;
	exec->nbr_arg = 0;
	exec->nbr_var_env = 0;
	exec->out = 0;
	exec->is_pipe = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_exec exec;

	(void)argc;
	(void)argv;
	// init all variable of the struct
	init_all(&exec);
	// copy env in a variable env
	if (!copy_env1(envp, &exec))
		return (1);
	// security
	if (!exec.env)
		return (1);
	// count the number of variable in env
	exec.nbr_var_env = ft_envlen(exec.env);
	// make a copy of env but in order in env_sorted
	if (!copy_env_sorted(&exec))
		return (1);
	// security
	if (!exec.env_sorted)
		return (1);
	// get the cmd 
	exec.cmd = ft_strdup(tab_arg[0]);
	// get the number of argument after cmd
	exec.nbr_arg = ft_tablen(tab_arg);
	// Test path
	exec.path = ft_strdup(exec.env[find_var_path(exec.env)][1]);
	//ft_printf("PATH: %s\n", exec.path);
	// Look at the command
	if (!identification(tab_arg, &exec))
		return (ft_printf("Not a command valid\n"), 1);
	//apply_path(exec.env, exec.cmd);
	free_all(&exec);
	return (0);
}

// variable avec une value de ./exec . Est ce normal ??
// Attention faire les test dans bash pas dans zsh (pas le meme resultat)
// -> Refaire les tests des builtins !!!
