                           
#include "minishell.h"

int builtin_echo(t_shell *shell)
{
    int i;
    char **arg;
    
    i = 1;
    arg = shell->cmd_list->args;
    if (arg[1] == NULL)
    {
        ft_printf("\n");
        return (exit_codes(shell, SUCCESS), 0);
    }
    else if (ft_strncmp("-n", arg[1], 2) == 0)
    {
        i = 2;
        if (!ft_printf_arg(arg, i, 1))
            return (exit_codes(shell, SUCCESS), 0);
    }
    else
    {
        if (!ft_printf_arg(arg, i, 0))
            return (exit_codes(shell, SUCCESS), 0);
    }
    return (1);
}

int builtin_cd(t_shell *shell)
{
    char    *path;
    t_exec *exec;
    char **arg;


    exec = shell->exec;
    arg = shell->cmd_list->args;
    if (exec->nbr_arg == 1)
    {
        if (!find_sth_in_env("HOME", exec->env))
            return (ft_printf("bash: cd: HOME not set\n"), 1);
        path = find_value_in_env("HOME", exec);
        change_oldpwd_or_pwd(exec, 1);
        if (!chdir(path))
            return (change_oldpwd_or_pwd(exec, 0), free(path), 1);
    }
    if (exec->nbr_arg == 2)
    {
        path = ft_strdup(arg[1]);
        change_oldpwd_or_pwd(exec, 1);
        if (!chdir(path))
            return (change_oldpwd_or_pwd(exec, 0), free(path), 1);
        ft_printf("bash: cd: no such file or directory: %s\n", path);
    }
    else if (exec->nbr_arg >= 3)
        return(ft_printf("bash: cd: too many arguments\n"), 1);
    return (0);
}

int builtin_pwd(t_shell *shell)
{
    char *path; 

    path = getcwd(NULL, 0);
    if (!path)
        return (0);
    printf("%s\n", path);
    free(shell->exec->oldpwd);
    shell->exec->oldpwd = ft_strdup("Hello");
    free(path);
    return (1);
}

int builtin_export(t_shell *shell)
{
    int i;
    char    *new_value;
    char    *new_variable;
    char    **arg;
    t_exec *exec;
    
    new_value = NULL;
    new_variable = NULL;
    exec = shell->exec;
    arg = shell->cmd_list->args;
    if (exec->nbr_arg >= 2)
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
