#include "../include/minishell.h"

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

int ft_env(char **envp, t_exec *exec)
{
    // copy env in a variable env
    if (!copy_env1(envp, exec))
		return (0);
    // security
    if (!exec.env)
		return (0);
    // count the number of variable in env
    exec.nbr_var_env = ft_envlen(exec.env);
    // make env_sorted
    if (!copy_env_sorted(exec))
		return (0);
    // security
    if (!exec.env_sorted)
		return (0);
    return (1);
}

int main(int argc, char **argv, char **envp)
{
    char *input;
    t_exec exec;

    (void)argc;
    (void)argv;
    if (!ft_env(envp, exec))
        return (1);
    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
        add_history(input);
        free(input);
    }
    // free all the variable of the struct (env, env_sorted)
    free_all_env(exec);
}
