/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:23:34 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/08 14:24:05 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_shell *shell)
{
	char	**arg;
	t_exec	*exec;
	int		number;

	arg = shell->cmd_list->args;
	exec = shell->exec;
	ft_printf("exit\n");
	if (exec->nbr_arg == 1)
		exec->out = 0;
	else if (exec->nbr_arg == 2)
	{
		number = ft_is_a_number(arg[1]);
		if (number)
			exec->out = ft_atoi(arg[1]);
		else
		{
			ft_printf("bash: exit: %s: numeric argument required\n", arg[1]);
			exec->out = 2;
		}
	}
	else if (exec->nbr_arg > 2 && ft_is_a_number(arg[1]))
	{
		exec->out = 1;
		ft_printf("bash: exit: too many arguments");
		return (1);
	}
	else if (exec->nbr_arg > 2 && !ft_is_a_number(arg[1]))
	{
		ft_printf("bash: exit: %s: numeric argument required\n", arg[1]);
		exec->out = 2;
	}
	free_all_env(exec);
	shell->exec->exit = 1;
	return (1);
}
