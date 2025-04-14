/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <williamcapt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:54:03 by wcapt             #+#    #+#             */
/*   Updated: 2025/04/12 19:06:36 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int builtin_unset(char **arg, t_exec *exec)
{
    (void)arg;
    (void)exec;
    ft_printf("unset\n");
    return (1);
}
int builtin_env(char **arg, t_exec *exec)
{
    (void)arg;
    (void)exec;
    ft_printf("env\n");
    return (1);
}
int builtin_exit(char **arg, t_exec *exec)
{
    (void)arg;
    (void)exec;
    free_env(exec->env);
    ft_printf("exit\n");
    return (1);
}
