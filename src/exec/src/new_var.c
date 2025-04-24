
#include "../../../include/exec.h"

int	new_var(char *new_value, char *new_variable, t_exec *exec)
{
	if (!new_var_env(new_value, new_variable, exec))
	{
        return (0);
	}
    if (!new_var_env_sorted(new_value, new_variable, exec))
    {    
		return (0);
	}
	return (1);
}

int	new_var_env(char *new_value, char *new_variable, t_exec *exec)
{
	char	***temp;
	int		i;
	int		j;
	
	i = 0;
    exec->nbr_var_env++;
    temp = malloc(sizeof(char **) * (exec->nbr_var_env + 1));
    if (!temp)
	{
        return (0);
	}
	while (exec->env[i])
	{
		j = 0;
		temp[i] = malloc(sizeof(char *) * 3);
		if (!temp[i])
			return (0);
		while (exec->env[i][j])
		{
			temp[i][j] = ft_strdup(exec->env[i][j]); 
			j++;
		}
		temp[i][j] = NULL;
		i++;
	}
	temp[i] = malloc(sizeof(char *) * 3);
	if (!temp[i])
		return (0);
	temp[i][0] = ft_strdup(new_variable);
	temp[i][1] = ft_strdup(new_value);
	temp[i][2] = NULL;
	temp[i + 1] = NULL;
	if (!free_env(exec->env))
		return (0);
	exec->env = temp;
	return (1);
}

int		new_var_env_sorted(char *new_value, char *new_variable, t_exec *exec)
{
	char	***temp;
	int		i; 
	int		j;
	int		place;
	
	i = 0;
	j = 0;
	place = find_var_place(new_variable, exec);
	temp = malloc(sizeof(char **) * (exec->nbr_var_env + 1));
	if (!temp)
		return (0);
	while (i < exec->nbr_var_env)
	{
		temp[i] = malloc(sizeof(char *) * 3);
		if (!temp[i])
			return (0);
		if (i == place)
		{
			temp[i][0] = ft_strdup(new_variable);
			temp[i][1] = ft_strdup(new_value);
			temp[i][2] = NULL;
		}
		else
		{
			temp[i][0] = ft_strdup(exec->env_sorted[j][0]);
			temp[i][1] = ft_strdup(exec->env_sorted[j][1]);
			temp[i][2] = NULL;
			j++;
		}
		i++;
	}
	temp[i] = NULL;
	if (!free_env(exec->env_sorted))
		return (0);
	exec->env_sorted = temp;
	return (1);
}

int	replace_value_var(char *new_value, int i, char ***env)
{
	free(env[i][1]);
	env[i][1] = ft_strdup(new_value);
	if (!env[i][1])
		return (0);
	return (1);
}

