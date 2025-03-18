/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:54:07 by wcapt             #+#    #+#             */
/*   Updated: 2025/03/18 16:34:53 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int main(int argc, char **argv, char **envp)
{
    (void)argv;
    char ***env;
    char *command;

    if (argc != 2)
        return (printf("The number of arguments is wrong!\n"), 1);
    command = argv[1];
    env = copy_env(envp);
    if (!env) 
        return (1);
    print_env(env);
    printf("PATH: %s\n", env[find_var_path(env)][1]);
    apply_path(env, command);
    return (0);
}
