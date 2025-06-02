
#include "../../../include/exec.h"

/*
void	init_all(t_exec *exec)
{
	exec->args = NULL;
	exec->line = 0;
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

int ft_exec(char ***tab_arg, t_exec *exec)
{
	init_all(exec);
	exec->nbr_var_env = ft_envlen(exec->env);
	exec->nbr_process = ft_tablen_3d(tab_arg);
	exec->nbr_pipes = exec->nbr_process - 1;
	exec->path = ft_strdup(exec->env[find_var_path(exec->env)][1]);
	exec->line = 0;
	// Look at the command
	if (!identification(tab_arg, exec, exec->line))
		return (ft_printf("Not a command valid\n"), 1);
	if (!pipeline(tab_arg, exec))
		return (ft_printf("Not a command valid\n"), 1);
	//apply_path(exec);
	free_var(exec);
	free_all_env(exec);
	return (1);
}
*/


char ***tab_arg = (char **[]) {
    (char *[]){"ls", NULL},
	(char *[]){"wc", "-l", NULL},
    NULL
};

void	init_all(t_exec *exec)
{
	exec->args = NULL;
	exec->line = 0;
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
	init_all(&exec); // init variables
	if (!copy_env1(envp, &exec)) // copy env in a variable env
		return (1);
	if (!exec.env) // security
		return (1);
	exec.nbr_var_env = ft_envlen(exec.env);
	exec.nbr_process = ft_tablen_3d(tab_arg);
	exec.nbr_pipes = exec.nbr_process - 1;
	exec.path = ft_strdup(exec.env[find_var_path(exec.env)][1]);
	exec.line = 0;
	// Look at the command
	if (exec.nbr_process == 1) // if the cmd is not a pipeline
	{
		printf("I m a simple command !!!\n");
		if (!identification(tab_arg, &exec, exec.line))
			return (ft_printf("Not a command valid\n"), 1);
	}
	else if (exec.nbr_process > 1) // if the cmd is a pipeline
	{
		printf("I m a pipeline !!!\n");
		if (!pipeline(tab_arg, &exec))
			return (ft_printf("Not a command valid\n"), 1);
	}
	free_var(&exec);
	free_all_env(&exec);
	return (0);
}




// variable avec une value de ./exec . Est ce normal ??
// Attention faire les test dans bash pas dans zsh (pas le meme resultat)
// -> Refaire les tests des builtins !!!
