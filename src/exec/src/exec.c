
#include "../../../include/exec.h"


void	init_all(t_exec *exec)
{
	exec->args = NULL;
	exec->cmd = NULL;
	exec->cmd_path = NULL;
	exec->path = NULL;
	exec->fd_in = 0;
	exec->nbr_arg = 0;
	exec->nbr_var_env = 0;
	exec->out = 0;
	exec->is_pipe = 0;
}

ft_exec(char **tab_arg, t_exec *exec)
{
	// init all variable of the struct
	init_all(exec);
	// get the cmd 
	exec->cmd = ft_strdup(tab_arg[0]);
	// get the number of argument after cmd
	exec->nbr_arg = ft_tablen(tab_arg);
	// Test path
	exec->path = ft_strdup(exec->env[find_var_path(exec->env)][1]);
	//ft_printf("PATH: %s\n", exec->path);
	if (!identification(tab_arg, exec))
		return (ft_printf("Not a command valid\n"), 0);
	free_var(exec);
	return (1);
}


/*
char *tab_arg[] = {"export", NULL}; 

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
	//apply_path(exec);
	free_var(&exec);
	free_all_env(&exec);
	return (0);
}
*/



// variable avec une value de ./exec . Est ce normal ??
// Attention faire les test dans bash pas dans zsh (pas le meme resultat)
// -> Refaire les tests des builtins !!!
