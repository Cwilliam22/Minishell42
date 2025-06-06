                           
#include "../../../include/exec.h"

int builtin_echo(char **arg, t_exec *exec)
{
    int i;

    i = 1;
    (void)exec;
    if (ft_strncmp("-n", arg[1], 2) == 0)
    {
        i = 2;
        if (!ft_printf_arg(arg, i, 1))
            return (0);
    }
    else
    {
        if (!ft_printf_arg(arg, i, 0))
            return (0);
    }
    return (1);
}

int builtin_cd(char **arg, t_exec *exec)
{
    char    *path;

    if (exec->nbr_arg == 1)
    {
        path = find_value_in_env("HOME", exec);
        if (!chdir(path))
            return (free(path), 1);
    }
    if (exec->nbr_arg == 2)
    {
        path = ft_strdup(arg[1]);
        if (!chdir(path))
            return (free(path), 1);
        ft_printf("cd: no such file or directory: %s\n", path);
    }
    else if (exec->nbr_arg == 3)
        return (ft_printf("cd: string not in pwd: %s\n", arg[1]), 1);
    else if (exec->nbr_arg >= 4)
        return(ft_printf("cd: too many arguments\n"), 1);
    ft_printf("cd\n");
    return (0);
}

int builtin_pwd(char **arg, t_exec *exec)
{
    char *path; 
    
    (void)exec;
    if (arg[1] != NULL)
        return (ft_printf("pwd: too many arguments\n"), 0);
    path = getcwd(NULL, 0);
    if (!path)
        return (0);
    printf("%s\n", path);
    free(path);
    // change the old pwd in the env !!!
    return (1);
}

int builtin_export(char **arg, t_exec *exec)
{
    int i;
    char    *new_value;
    char    *new_variable;
    
    new_value = NULL;
    new_variable = NULL;
    if (exec->nbr_arg == 4)
    {
        new_value = ft_strdup(arg[3]);
        new_variable = ft_strdup(arg[1]);
    }
    if (exec->nbr_arg == 1)
    {
        if (!print_env_sorted(exec))
            return (0);
    }
    else if (exec->nbr_arg == 4)
    {
        i = find_sth_in_env(arg[1], exec->env);
        if (i == -1)
        {
            if (!new_var(new_value, new_variable, exec))
                return (0);
        }
        else if (!replace_value_var(new_value, i, exec->env))
                return (0);
    }
    if (new_value != NULL || new_variable != NULL)
    {
        free(new_value);
        free(new_variable);
    }
    return (1);
}
