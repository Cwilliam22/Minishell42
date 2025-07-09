/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:27:28 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/09 14:07:01 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_shell *shell)
{
	char	**arg;
	t_exec	*exec;

	arg = shell->cmd_list->args;
	exec = shell->exec;
	if (exec->nbr_arg == 1)
	{
		if (!print_env(exec->env))
			return (1);
	}
	else if (exec->nbr_arg != 1)
	{
		ft_printf("env: ‘%d’: No such file or directory\n", arg[1]);
		return (127);
	}
	return (0);
}
