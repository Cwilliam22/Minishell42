/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:39:34 by wcapt             #+#    #+#             */
/*   Updated: 2025/03/22 17:08:00 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void    identification()
{
	if (its_a_builtin())
	{
		execute_builtin();
		return (1);
	}
	else
	{
		execute_externe();
		return (1);
	}
	return (0);
}

int	its_a_builtin()
{
	return (0);
}

void	execute_builtin(char *args, char ***env)
{
	int	i;
	t_builtin tab_link[] = {
		{"cd", builtin_cd},
		{"echo", builtin_echo},
		{"pwd", builtin_pwd},
		{"export", builtin_export},
		{"unset", builtin_unset},
		{"env", builtin_env},
		{"exit", builtin_exit},
		{NULL, NULL}};
		return (tab_link[i].fonction(args, env));
}
void	execute_externe()
{
}
