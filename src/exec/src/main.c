/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:54:07 by wcapt             #+#    #+#             */
/*   Updated: 2025/03/22 15:33:43 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	main(int argc, char **argv, char **envp)
{
	char	***env;
	char	*command;

	(void)argv;
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
