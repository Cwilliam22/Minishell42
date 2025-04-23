/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:54:03 by wcapt             #+#    #+#             */
/*   Updated: 2025/04/23 15:30:22 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

int builtin_unset(char **arg, t_exec *exec)
{
    (void)arg;
    (void)exec;
    ft_printf("unset\n");
    return (1);
}

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
    ft_printf("env\n");
    return (1);
}

int builtin_exit(char **arg, t_exec *exec)
{
    (void)arg;
    free_all(exec);
    ft_printf("exit\n");
    return (1);
}
