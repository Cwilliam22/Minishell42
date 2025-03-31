/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: william <william@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:54:03 by wcapt             #+#    #+#             */
/*   Updated: 2025/03/31 14:54:25 by william          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int builtin_unset(char *arg, char ***env)
{
    apply_path(env, arg);
    ft_printf("unset\n");
    return (1);
}
int builtin_env(char *arg, char ***env)
{
    apply_path(env, arg);
    ft_printf("env\n");
    return (1);
}
int builtin_exit(char *arg, char ***env)
{
    apply_path(env, arg);
    ft_printf("exit\n");
    return (1);
}
