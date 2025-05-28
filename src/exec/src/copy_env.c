
#include "../../../include/exec.h"


// Revoir la fonction car elle ne split pas correctement les variables dans env
// ce qui donne des erreurs dans la suite de l'exec !!!!!!!!!!
char	**split_var_env(char *env_var)
{
	char	*sign;
	char	**split;

	split = malloc(3 * sizeof(char *));
	if (!split)
		return (NULL);
	sign = ft_strchr(env_var, '=');
	printf("%s\n", env_var);
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

char	**copy_env_sorted(t_exec *exec)
{
	int i;
	int count;
	char **dest;

	i = 0;
	count = 0;
	while (exec->env[count])
		count++;
	dest = malloc(sizeof(char *) * (count + 1));
	if (!dest)
		return (NULL);
	while (i < count)
	{
		dest[i] = ft_strdup(exec->env[i][0]);
		i++;
	}
	dest[i] = NULL;
	ft_sort_array(dest);
	return (dest);
}


int	print_env_sorted(t_exec *exec)
{
	int	i;
	int j;
	char **temp;

	i = 0;
	temp = copy_env_sorted(exec);
	while (temp[i])
	{
		j = 0;
		while (exec->env[j])
		{
			if (ft_strcmp(temp[i], exec->env[j][0]) == 0)
			{
				ft_printf("declare -x %s=\"%s\"\n", exec->env[j][0], exec->env[j][1]);
				break;
			}
			j++;
		}
		i++;
	}
	free_array(temp);
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
