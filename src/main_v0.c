#include "../include/minishell.h"

#include <stdio.h>

void print_char_triple_array(char ***tab) 
{
    int i;
    int j;

    i = 0;

    if (!tab)
        return;
    while (tab[i] != NULL) 
    {
        printf("Command %d:\n", i);
        j = 0;
        while (tab[i][j] != NULL) 
        {
            printf("  arg[%d] = %s\n", j, tab[i][j]);
            j++;
        }
        i++;
    }
}

char ***create_tab(int argc, char *input)
{

    char ***tab;
    int nbr_words;
   
    nbr_words = argc - 1;
    tab = malloc(sizeof(char **) * (nbr_words + 1));
    if (!tab)
        return (NULL);
    tab[0] = malloc(sizeof(char *) * 2);
    tab[0][0] = ft_strdup(input);
    tab[0][1] = NULL;
    tab[nbr_words] = NULL;
    return (tab);
}

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
    char ***tab;

    (void)argv;
	exec.env = NULL;
    if (!ft_env(envp, &exec))
        return (1);
    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
        // pasrse(input)
        tab = create_tab(argc, input);
        print_char_triple_array(tab);
        ft_exec(tab, &exec);
        add_history(input);
        free(input);
    }
    // free all the variable of the struct (env, env_sorted)
    free_all_env(&exec);
}
