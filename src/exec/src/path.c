
#include "../../../include/exec.h"

int	find_var_path(char ***env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] && env[i][1] && ft_strcmp(env[i][0], "PATH") == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*read_in_path(char ***env, int place)
{
	char	*src;
	char	*path;
	int		i;

	if (!env[place] || !env[place][1])
		return (NULL);
	src = env[place][1];
	i = 0;
	while (src[i])
		i++;
	path = malloc(sizeof(char) * (i + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (src[i])
	{
		path[i] = src[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

int apply_path(t_exec *exec)
{
    char **paths;
    char *test_path;
	char *tmp;
    int i;

	printf("Je suis dans apply_path !!!\n");
	printf("place of path : %d\n", find_var_path(exec->env));
	//print_env(exec->env);
    paths = ft_split(read_in_path(exec->env, find_var_path(exec->env)), ':');
	printf("test 1\n");
    if (!paths)
	{
        return (0);
	}
	printf("Je suis encore dans apply_path ... \n");
    i = 0;
	printf("paths: %s\n", paths[0]);
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
		test_path = ft_strjoin(tmp, exec->cmd);
		free(tmp);
		printf("Test path: %s\n", test_path);
        if (access(test_path, X_OK) == 0)
        {
            exec->cmd_path = test_path;
            free_array(paths);
            return (1);
        }
        free(test_path);
        i++;
    }
    free_array(paths);
    return (ft_printf("Commande not found!\n"), 0);
}
