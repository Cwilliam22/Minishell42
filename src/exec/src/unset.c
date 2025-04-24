
#include "../../../include/exec.h"

int	unset_var(int index, t_exec *exec)
{
	if (!unset_var_env(index, exec))
	{
        return (0);
	}
    if (!unset_var_env_sorted(index, exec))
    {    
		return (0);
	}
	return (1);
}

int unset_var_env(int index, t_exec *exec)
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

int unset_var_env_sorted(int index, t_exec *exec)
{
    char	***temp;
	int		i;
	int		j;
    int     m;
	
	i = 0;
    m = 0;
    temp = malloc(sizeof(char **) * (exec->nbr_var_env + 1));
    if (!temp)
        return (0);
    while (exec->env_sorted[m])
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
        while (exec->env_sorted[m][j])
        {
            temp[i][j] = ft_strdup(exec->env_sorted[m][j]);
            j++;
        }
        temp[i][j] = NULL;
        i++;
        m++;
    }
    temp[i] = NULL;
    if (!free_env(exec->env_sorted))
		return (0);
	exec->env_sorted = temp;
    return (1);
}

