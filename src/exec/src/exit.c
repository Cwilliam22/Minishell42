/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:23:34 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/09 22:19:53 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exit_error(char *arg, char *msg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

static int	handle_single_arg(char *arg)
{
	int	exit_code;

	if (ft_is_a_number(arg))
	{
		exit_code = ft_atoi(arg);
		return ((exit_code % 256 + 256) % 256);
	}
	else
	{
		print_exit_error(arg, "numeric argument required");
		return (2);
	}
}

static int	handle_multiple_args(char *arg)
{
	if (ft_is_a_number(arg))
	{
		print_exit_error(NULL, "too many arguments");
		return (1);
	}
	else
	{
		print_exit_error(arg, "numeric argument required");
		return (2);
	}
}

static int	get_exit_code(t_exec *exec, char **arg)
{
	if (exec->nbr_arg == 1)
		return (0);
	else if (exec->nbr_arg == 2)
		return (handle_single_arg(arg[1]));
	else
		return (handle_multiple_args(arg[1]));
}

int	builtin_exit(t_shell *shell)
{
	char	**arg;
	t_exec	*exec;
	int		exit_code;

	arg = shell->cmd_list->args;
	exec = shell->exec;
	ft_printf("exit\n");
	exit_code = get_exit_code(exec, arg);
	if (exec->nbr_arg > 2 && ft_is_a_number(arg[1]))
		return (shell->exit_status = 1, 1);
	free_all_env(exec);
	exit(exit_code);
}
