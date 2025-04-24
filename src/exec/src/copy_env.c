
#include "../../../include/exec.h"

char	**split_var_env(char *env_var)
{
	char	*sign;
	char	**split;

	split = malloc(3 * sizeof(char *));
	if (!split)
		return (NULL);
	sign = ft_strchr(env_var, '=');
	if (!sign)
	{
		split[0] = ft_strdup(env_var);
		split[1] = NULL;
	}
	else
	{
		*sign = '\0';
		split[0] = ft_strdup(env_var);
		split[1] = ft_strdup(sign + 1);
		split[2] = NULL;
	}
	return (split);
}

int	copy_env1(char **envp, t_exec *exec)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	exec->env = malloc((i + 1) * sizeof(char **));
	if (!exec->env)
		return (0);
	while (j < i)
	{
		exec->env[j] = split_var_env(envp[j]);
		j++;
	}
	exec->env[i] = NULL;
	return (1);
}

int	print_env(char ***env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][1])
			ft_printf("%s=%s\n", env[i][0], env[i][1]);
		else
		    ft_printf("%s=NULL\n", env[i][0]);
		i++;
	}
	return (1);
}

int	print_env_sorted(char ***env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("declare -x ");
		if (env[i][1])
			ft_printf("%s=%s\n", env[i][0], env[i][1]);
		else
		    ft_printf("%s=NULL\n", env[i][0]);
		i++;
	}
	return (1);
}

int	copy_env_sorted(t_exec *exec)
{
	int	i;
	int	j;
	int place;
	
	i = 0;
	if (exec->env_sorted)
		free_env(exec->env_sorted);
	exec->env_sorted = malloc((exec->nbr_var_env + 1) * sizeof(char **));
	if (!exec->env_sorted)
		return (0);
	while (i < exec->nbr_var_env)
	{
		j = 0;
		place = get_var_in_order(i, exec);
		exec->env_sorted[i] = malloc(3 * sizeof(char *));
		if (!exec->env_sorted[i])
			return (0);
		while (exec->env[place][j])
		{
			exec->env_sorted[i][j] = ft_strdup(exec->env[place][j]);
			j++;
		}
		exec->env_sorted[i][j] = NULL;
		i++;
	}
	exec->env_sorted[i] = NULL;
	return (1);
}

/*
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char ***env;

	env = copy_env(envp);
	if (!env) 
		return (1);
	print_env(env);
	return (0);
}
*/
