#include "../include/minishell.h"

int ft_env(char **envp, t_exec *exec)
{
  if (!copy_env1(envp, exec))
		return (0);
  if (!exec->env)
		return (0);
  exec->nbr_var_env = ft_envlen(exec->env);
  return (1);
}

int main(int argc, char **argv, char **envp)
{
    char *input;
    t_exec exec;

    (void)argc;
    (void)argv;
	  exec.env = NULL;
    if (!ft_env(envp, &exec))
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
    free_all_env(&exec);
}
