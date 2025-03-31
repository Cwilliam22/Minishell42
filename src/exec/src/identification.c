/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: william <william@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:39:34 by wcapt             #+#    #+#             */
/*   Updated: 2025/03/31 15:08:22 by william          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

t_builtin tab_link[] = {
	{"cd", builtin_cd},
	{"echo", builtin_echo},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{NULL, NULL}};

int    identification(char *arg, char ***env)
{
	if (its_a_builtin(arg, env))
		return (1);
	else
	{
		execute_externe(arg, env);
		return (1);
	}
	return (0);
}

int	its_a_builtin(char *arg, char ***env)
{
	int	i;

	i = 0;
		while (tab_link[i].builtin != NULL) 
		{
			if (ft_strcmp(arg, tab_link[i].builtin) == 0)
				return (tab_link[i].fonction(arg, env));
			i++;
		}
		return (0);
}

int	execute_externe(char *arg, char ***env)
{
	(void)env;
	(void)arg;
	ft_printf("execute_externe\n");
	return (1);
}
