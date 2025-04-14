
#include "../include/exec.h"

int free_env(char ***env)
{
    int i;
    int j;

    i = 0;
    if (!env)
        return (0);
    while (env[i])
    {
        j = 0;
        while (env[i][j])
        {
            free(env[i][j]);
            j++;
        }
        free(env[i]);
        i++;
    }
    free(env);
    env = NULL;
    return (1);
}

int free_array(char **array)
{
    int i;

    i = 0;
    if (!array)
        return (0);
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
    return (1);
}
