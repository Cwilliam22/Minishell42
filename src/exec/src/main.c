/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <williamcapt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:54:07 by wcapt             #+#    #+#             */
/*   Updated: 2025/04/10 16:02:12 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

char *tab_arg[] = {"export", "CACA", "=", "/bin", NULL}; 
//"export PATH=/bin"

void	init_all(t_exec *exec)
{
	exec->args = NULL;
	exec->env_sorted = NULL;
	exec->env = NULL;
	exec->cmd = NULL;
	exec->cmd_path = NULL;
	exec->path = NULL;
	exec->fd_in = 0;
	exec->nbr_arg = 0;
	exec->nbr_var_env = 0;
	exec->fd_out = 0;
	exec->is_pipe = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_exec exec;

	init_all(&exec);
	(void)argc;
	(void)argv;
	// Variable command
	exec.cmd = tab_arg[0];
	// Count args
	exec.nbr_arg = ft_tablen(tab_arg);
	// Copy env in a variable (char *** type)
	exec.env = copy_env1(envp);
	if (!copy_env_sorted(&exec))
		return (1);
	exec.nbr_var_env = ft_envlen(exec.env);
	// Security
	if (!exec.env)
		return (1);
	// Test tab ***
	if (!print_env(exec.env_sorted))
		return (1);
	if (!print_env(exec.env))
		return (1);
	// Test path
	exec.path = ft_strdup(exec.env[find_var_path(exec.env)][1]);
	//printf("PATH: %s\n", exec.path);
	// Look at the command
	if (!identification(tab_arg, &exec))
		return (ft_printf("Not a command valid\n"), 1);
	apply_path(exec.env, exec.cmd);
	return (0);
}
