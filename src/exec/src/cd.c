/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:25:06 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/09 16:02:03 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_cd(char *path, int way)
{
	ft_putstr_fd("bash: cd: ", way);
	ft_putstr_fd(path, way);
	ft_putendl_fd(": No such file or directory:", way);
}

int	builtin_cd(t_shell *shell)
{
	char	*path;
	char	**arg;

	arg = shell->cmd_list->args;
	if (shell->exec->nbr_arg == 1)
	{
		if (!find_sth_in_env("HOME", shell->exec->env))
			return (ft_printf("bash: cd: HOME not set\n"), 1);
		path = find_value_in_env("HOME", shell->exec);
		change_oldpwd_or_pwd(shell->exec, 1);
		if (!chdir(path))
			return (change_oldpwd_or_pwd(shell->exec, 0), free(path), 0);
	}
	else if (shell->exec->nbr_arg >= 2)
	{
		path = ft_strdup(arg[1]);
		change_oldpwd_or_pwd(shell->exec, 1);
		if (!chdir(path))
			return (change_oldpwd_or_pwd(shell->exec, 0), free(path), 0);
		print_error_cd(path, STDERR);
	}
	return (1);
}
