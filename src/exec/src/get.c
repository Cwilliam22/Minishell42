
#include "minishell.h"

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

int	get_var_in_order(int index, t_exec *exec)
{
	int		i;
	char	**temp;
	char	**sorted;
	char	*target;

	i = 0;
	temp = malloc(sizeof(char *) * (exec->nbr_var_env + 1));
	if (!temp)
		return (0);
	while (exec->env[i])
	{
		temp[i] = ft_strdup(exec->env[i][0]);
		i++;
	}
	temp[i] = NULL;
	sorted = ft_sort_array(temp);
	target = ft_strdup(sorted[index]);
	free_array(sorted);
	if (!target)
		return (0);
	i = 0;
	while (exec->env[i])
	{
		if (ft_strcmp(exec->env[i][0], target) == 0)
		{
			free(target);
			return (i);
		}
		i++;
	}
	free(target);
	return (0);
}
