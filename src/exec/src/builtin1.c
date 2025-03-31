/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: william <william@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:54:09 by wcapt             #+#    #+#             */
/*   Updated: 2025/03/31 14:53:54 by william          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int builtin_echo(char *arg, char ***env)
{
    apply_path(env, arg);
    ft_printf("echo\n");
    return (1);
}

int builtin_cd(char *arg, char ***env)
{
    apply_path(env, arg);
    ft_printf("cd\n");
    return (1);
}

int builtin_pwd(char *arg, char ***env)
{
    apply_path(env, arg);
    ft_printf("pwd\n");
    return (1);
}

int builtin_export(char *arg, char ***env)
{
    apply_path(env, arg);
    ft_printf("export\n");
    return (1);
}