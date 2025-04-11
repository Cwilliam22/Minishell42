
#include "../include/exec.h"

int ft_envlen(char ***env)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    return (i);
}

int ft_tablen(char **tab_arg)
{
	int	args;

	args = 0;
	while (tab_arg[args])
		args++;
	return (args);
}
