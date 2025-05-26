
#include "../../../include/exec.h"

int ft_envlen(char ***env)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    return (i);
}

int ft_tablen_3d(char ***tab_arg)
{
	int	process;

	process = 0;
	while (tab_arg[process])
		process++;
	return (process);
}

int ft_tablen_2d(char **tab_arg)
{
    int	args;

	args = 0;
	while (tab_arg[args])
		args++;
	return (args);
}
