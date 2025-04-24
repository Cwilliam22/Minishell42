
#include "../../../include/exec.h"

int builtin_unset(char **arg, t_exec *exec)
{
    int i;
    int place;
    
    i = 0;
    if (exec->nbr_arg == 1)
        return (1);
    else 
    {
        while (arg[i])
        {
            place = find_sth_in_env(arg[i], exec->env);
            if (place != -1)
                unset_var(place, exec);
            i++;
        }
    }
    return (1);
}

// unset sans arguments ne fais rien
// unset avec une variable fausse ne fait rien
// unset une variable existante efface la variable de l'env
// unset avec plusieurs arguments appliquera unset sur chaque argument individuellement
    // regarder en plus les cas précédent pour les applications individuelle 

int builtin_env(char **arg, t_exec *exec)
{
    if (exec->nbr_arg == 1)
    {
        if (!print_env(exec->env))
		    return (0);
    }
    else if (exec->nbr_arg != 1)
    {
        ft_printf("env: ‘%d’: No such file or directory\n", arg[1]);
    }
    return (1);
}

int builtin_exit(char **arg, t_exec *exec)
{
    ft_printf("exit\n");
    if (exec->nbr_arg == 1)
        exec->out = 0;
    else if (exec->nbr_arg == 2 && ft_is_a_number(arg[1]))
        exec->out = ft_atoi(arg[1]);
    else if (exec->nbr_arg == 2 && !ft_is_a_number(arg[1]))
    {
        ft_printf("bash: exit: %s: numeric argument required\n", arg[1]);
        exec->out = 2;
    }
    else if (exec->nbr_arg > 2 && ft_is_a_number(arg[1]))
    {
        exec->out = 1;
        ft_printf("bash: exit: too many arguments");
        return (1);
    }
    else if (exec->nbr_arg > 2 && !ft_is_a_number(arg[1]))
    {
        ft_printf("bash: exit: %s: numeric argument required\n", arg[1]);
        exec->out = 2;
    }
    free_all(exec);
    exit(exec->out);
    return (1);
}

// regarde toujour le deuxieme argument 
