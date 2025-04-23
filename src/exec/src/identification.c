/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:39:34 by wcapt             #+#    #+#             */
/*   Updated: 2025/04/23 15:30:58 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/exec.h"

t_builtin tab_link[] = {
	{"cd", builtin_cd},
	{"echo", builtin_echo},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{NULL, NULL}};

int    identification(char **arg, t_exec *exec)
{
	if (its_a_builtin(arg, exec))
		return (1);
	else
	{
		execute_externe(arg, exec->env);
		return (1);
	}
	return (0);
}

int	its_a_builtin(char **arg, t_exec *exec)
{
	int	i;

	i = 0;
		while (tab_link[i].builtin != NULL) 
		{
			if (ft_strcmp(arg[0], tab_link[i].builtin) == 0)
				return (tab_link[i].fonction(arg, exec));
			i++;
		}
		return (0);
}

int	execute_externe(char **arg, char ***env)
{
	(void)env;
	(void)arg;
	ft_printf("execute_externe\n");
	return (1);
}
