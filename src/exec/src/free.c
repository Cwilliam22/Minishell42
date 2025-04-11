
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

