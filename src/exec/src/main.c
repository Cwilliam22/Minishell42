/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: william <william@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:54:07 by wcapt             #+#    #+#             */
/*   Updated: 2025/03/31 14:52:24 by william          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	main(int argc, char **argv, char **envp)
{
	char	***env;
	char	*command;

	(void)argv;
	// Nbr argument (executable + command)
	if (argc != 2)
		return (printf("The number of arguments is wrong!\n"), 1);
	// Variable command
	command = argv[1];
	// Copy env in a variable (char *** type)
	env = copy_env(envp);
	// Security
	if (!env)
		return (1);
	// Test tab ***
	print_env(env);
	// Test path
	printf("PATH: %s\n", env[find_var_path(env)][1]);
	// Look at the command
	if (!identification(command, env))
		return (ft_printf("Not a command valid\n"), 1);
	
	apply_path(env, command);
	
	return (0);
}
