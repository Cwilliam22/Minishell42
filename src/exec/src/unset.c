
#include "../../../include/exec.h"

int unset_var(int index, t_exec *exec)
{
    char	***temp;
	int		i;
	int		j;
    int     m;
	
	i = 0;
    m = 0;
    exec->nbr_var_env--;
    temp = malloc(sizeof(char **) * (exec->nbr_var_env + 1));
    if (!temp)
        return (0);
    while (exec->env[m])
    {
        if (m == index)
        {
            m++;
            continue;
        }
        j = 0;
        temp[i] = malloc(sizeof(char *) * 3);
        if (!temp[i])
            return (0);
        while (exec->env[m][j])
        {
            temp[i][j] = ft_strdup(exec->env[m][j]);
            j++;
        }
        temp[i][j] = NULL;
        i++;
        m++;
    }
    temp[i] = NULL;
    if (!free_env(exec->env))
		return (0);
	exec->env = temp;
    return (1);
}


