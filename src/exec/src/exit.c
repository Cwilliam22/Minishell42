/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:23:34 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/09 14:05:02 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	conditions_exit(t_exec *exec, int number, char **arg)
{
	if (exec->nbr_arg == 1)
		return (0);
	else if (exec->nbr_arg == 2)
	{
		number = ft_is_a_number(arg[1]);
		if (number)
			return (ft_atoi(arg[1]));
		else
		{
			ft_printf("bash: exit: %s: numeric argument required\n", arg[1]);
			return (2);
		}
	}
	else if (exec->nbr_arg > 2 && ft_is_a_number(arg[1]))
	{
		ft_printf("bash: exit: too many arguments");
		return (1);
	}
	else if (exec->nbr_arg > 2 && !ft_is_a_number(arg[1]))
	{
		ft_printf("bash: exit: %s: numeric argument required\n", arg[1]);
		return (2);
	}
	return (-1);
}

int	builtin_exit(t_shell *shell)
{
	char	**arg;
	t_exec	*exec;
	int		number;

	arg = shell->cmd_list->args;
	exec = shell->exec;
	number = 0;
	ft_printf("exit\n");
	if (conditions_exit(exec, number, arg) == -1)
		return (1);
	free_all_env(exec);
	return (0);
}
