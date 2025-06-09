
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

	printf("Test 1\n");
    paths = ft_split(read_in_path(exec->env, find_var_path(exec->env)), ':');
    if (!paths)
	{
        return (0);
	}
    i = 0;
	printf("Test 2\n");
    while (paths[i])
    {
		printf("Test 3\n");
        tmp = ft_strjoin(paths[i], "/");
		printf("tmp: %s\n", tmp);
		printf("exec->cmd: %s\n", exec->cmd);
		test_path = ft_strjoin(tmp, exec->cmd);
		printf("test_path: %s\n", test_path);
		free(tmp);
		printf("Trying path: %s\n", test_path);
        if (access(test_path, X_OK) == 0)
        {
			printf("Test 4\n");
			printf("cmd_path : %s\n", exec->cmd_path);
            exec->cmd_path = test_path;
            free_array(paths);
            return (1);
        }
        free(test_path);
        i++;
		printf("Test 5\n");
    }
    free_array(paths);
    return (ft_printf("Command not found!\n"), 0);
}
