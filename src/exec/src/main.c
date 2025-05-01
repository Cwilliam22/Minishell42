
#include "../../../include/exec.h"

ft_exec(char **tab_arg, t_exec *exec)
{
	// init all variable of the struct
	init_all(exec);
	// get the cmd 
	exec.cmd = ft_strdup(tab_arg[0]);
	// get the number of argument after cmd
	exec.nbr_arg = ft_tablen(tab_arg);
	// Test path
	exec.path = ft_strdup(exec.env[find_var_path(exec.env)][1]);
	//ft_printf("PATH: %s\n", exec.path);
	// Look at the command
	if (!identification(tab_arg, exec))
		return (ft_printf("Not a command valid\n"), 0);
	//apply_path(exec.env, exec.cmd);
	// Make another function to not free env and env_sorted 
	free_var(exec);
	return (1);
}

// variable avec une value de ./exec . Est ce normal ??
// Attention faire les test dans bash pas dans zsh (pas le meme resultat)
// -> Refaire les tests des builtins !!!
