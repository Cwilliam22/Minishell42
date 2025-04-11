
#include "../include/exec.h"

int	find_sth_in_env(char *variable, char ***env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i][0], variable) == 0)
			return (printf("place of variable : %d\n", i), i);
		i++;
	}
	return (printf("variable not found : -1\n"), -1);
}

char	*find_value_in_env(char *variable, t_exec *exec)
{
	char *value;
	int	i;
	
	i = 0;
	while (ft_strcmp(exec->env[i][0], variable) != 0)
		i++;
	if (ft_strcmp(exec->env[i][0], variable) == 0)
	{
		value = ft_strdup(exec->env[i][1]);
		return (value);
	}
	else 
		return (NULL);
}

int find_var_place(char *new_variable, t_exec *exec)
{
    int i;

    i = 0;
    while (exec->env_sorted[i])
    {
        if (ft_strcmp(new_variable, exec->env_sorted[i][0]) < 0)
            return (i);
        i++;
    }
    return (-1);
}

int	get_var_in_order(int index, t_exec *exec)
{
	int		i;
	char	**temp;
	
	i = 0;
	temp = malloc(sizeof(char *) * (exec->nbr_arg + 1));
	if (!temp)
		return (0);
	while (exec->env[i])
	{
		temp[i] = ft_strdup(exec->env[i][0]);
		i++;
	}
	temp = ft_sort_array(temp);
	i = 0;
	while (exec->env[i])
	{
		if (ft_strcmp(exec->env[i][0], temp[index]) == 0)
			return (i);
		i++;
	}
	return (0);
}
