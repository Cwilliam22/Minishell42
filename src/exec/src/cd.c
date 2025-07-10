/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:25:06 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/09 23:06:32 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cd_error(char *path, char *msg, int way)
{
	ft_putstr_fd("minishell: cd: ", way);
	if (path)
	{
		ft_putstr_fd(path, way);
		ft_putstr_fd(": ", way);
	}
	ft_putendl_fd(msg, way);
}

static int	handle_cd_home(t_shell *shell)
{
	char	*path;

	if (!find_sth_in_env("HOME", shell->exec->env))
	{
		print_cd_error(NULL, "HOME not set", STDERR);
		return (1);
	}
	path = find_value_in_env("HOME", shell->exec);
	change_oldpwd_or_pwd(shell->exec, 1);
	if (!chdir(path))
		return (change_oldpwd_or_pwd(shell->exec, 0), free(path), 0);
	free(path);
	return (1);
}

static int	handle_cd_path(t_shell *shell, char *target)
{
	char	*path;

	path = ft_strdup(target);
	change_oldpwd_or_pwd(shell->exec, 1);
	if (!chdir(path))
		return (change_oldpwd_or_pwd(shell->exec, 0), free(path), 0);
	print_cd_error(path, "No such file or directory", STDERR);
	free(path);
	return (1);
}

int	builtin_cd(t_shell *shell)
{
	char	**arg;

	arg = shell->cmd_list->args;
	if (shell->exec->nbr_arg > 2)
	{
		print_cd_error(NULL, "too many arguments", STDERR);
		return (1);
	}
	if (shell->exec->nbr_arg == 1)
		return (handle_cd_home(shell));
	else
		return (handle_cd_path(shell, arg[1]));
}