
#include "minishell.h"

int builtin_unset(t_shell *shell)
{
    int i;
    int place;
    char **arg;
    t_exec *exec;
    
    i = 0;
    arg = shell->cmd_list->args;
    exec = shell->exec;
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


int builtin_env(t_shell *shell)
{
    char **arg;
    t_exec *exec;

    arg = shell->cmd_list->args;
    exec = shell->exec;
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

int builtin_exit(t_shell *shell)
{
    char **arg;
    t_exec *exec;

    arg = shell->cmd_list->args;
    exec = shell->exec;
    ft_printf("exit\n");
    if (exec->nbr_arg == 1)
        exec->out = 0;
    else if (exec->nbr_arg == 2)
	{
		int	number = ft_is_a_number(arg[1]);
		if (number)
			exec->out = ft_atoi(arg[1]);
		else
		{
			ft_printf("bash: exit: %s: numeric argument required\n", arg[1]);
			exec->out = 2;
		}
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
    free_all_env(exec);
    exit(exec->out);
    return (1);
}

// regarde toujour le deuxieme argument 
