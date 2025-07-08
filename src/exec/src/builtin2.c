/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:27:28 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/08 14:23:47 by wcapt            ###   ########.fr       */
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
			return (0);
	}
	else if (exec->nbr_arg != 1)
	{
		return (ft_printf("env: ‘%d’: No such file or directory\n", arg[1]),
			exit_codes(shell, COMMAND_NOT_FOUND, ""), 0);
	}
	return (exit_codes(shell, SUCCESS, ""), 1);
}
