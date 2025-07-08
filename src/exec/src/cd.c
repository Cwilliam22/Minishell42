/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:25:06 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/08 16:12:32 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_shell *shell)
{
	char	*path;
	char	**arg;

	arg = shell->cmd_list->args;
	if (shell->exec->nbr_arg == 1)
	{
		if (!find_sth_in_env("HOME", shell->exec->env))
			return (ft_printf("bash: cd: HOME not set\n"),
				exit_codes(shell, GENERAL_ERROR, ""), 0);
		path = find_value_in_env("HOME", shell->exec);
		change_oldpwd_or_pwd(shell->exec, 1);
		if (!chdir(path))
			return (change_oldpwd_or_pwd(shell->exec, 0), free(path),
				exit_codes(shell, SUCCESS, ""), 1);
	}
	else if (shell->exec->nbr_arg >= 2)
	{
		path = ft_strdup(arg[1]);
		change_oldpwd_or_pwd(shell->exec, 1);
		if (!chdir(path))
			return (change_oldpwd_or_pwd(shell->exec, 0), free(path),
				exit_codes(shell, SUCCESS, ""), 1);
		ft_printf("bash: cd: no such file or directory: %s\n", path);
	}
	return (exit_codes(shell, GENERAL_ERROR, ""), 0);
}
