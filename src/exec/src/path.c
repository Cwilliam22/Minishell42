
#include "../../../include/exec.h"

int	find_var_path(char ***env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i][0], "PATH", 4) == 0)
			return (i);
		i++;
	}
	return (0);
}

char	*read_in_path(char ***env, int place)
{
	char	*path;
	int		i;

	i = 0;
	while (env[place][1][i])
		i++;
	path = malloc(sizeof(char) * (i + 1));
	if (!path)
		return (NULL);
	while (env[place][1][i])
	{
		path[i] = env[place][1][i];
		i++;
	}
	return (path);
}

int	apply_path(t_exec *exec)
{
	char	*path;
	char	*pathname;
	char	*temp;

	path = read_in_path(exec->env, find_var_path(exec->env));
	if (!path)
		return (0);
	while (*path)
	{
		pathname = ft_strfchr(path, ':');
		pathname = ft_strjoin(pathname, exec->cmd);
		temp = ft_strchr(path, ':');
		if (temp)
			path = ft_strdup(temp + 1);
		else
			path = ft_strdup("");
		if (access(pathname, F_OK) == 0)
		{
			if (access(pathname, X_OK) == 0)
			{
				exec->cmd_path = ft_strdup(pathname);
				return (free(pathname), free(path), 1);
			}
		}
		free(pathname);
	}
	return (free(path), printf("Commande not found!\n"), 0);
}
