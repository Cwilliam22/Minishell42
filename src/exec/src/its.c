/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:23:48 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/09 15:18:41 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_valid_identifier(char *arg)
{
	int i;

	i = 0;
	if (!ft_isalpha((int)arg[i]) && arg[i] != '_')
		return (0);
	i++;
	while (arg[i])
	{
		if (!ft_isalpha((int)arg[i]) &&
			!ft_isdigit((int)arg[i]) &&
			arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	look_at_identifier(t_shell *shell)
{
	int		i;
	char	**args;

	i = 0;
	args = shell->cmd_list->args;
	while (args[i])
	{
		if (!is_a_valid_identifier(args[i]))
			return (exit_codes(shell, GENERAL_ERROR, ""), 0);
		i++;
	}
	return (exit_codes(shell, SUCCESS, ""), 1);
}

int	its_absolute_path(t_shell *shell)
{
	if (shell->cmd_list->args[0][0] == '/')
		shell->exec->cmd_path = ft_strdup(shell->cmd_list->args[0]);
	if (!shell->exec->cmd_path)
		return (0);
	return (1);
}

int	its_relative_path(t_shell *shell)
{
	if (shell->cmd_list->args[0][0] == '.'
		&& shell->cmd_list->args[0][1] == '/')
		shell->exec->cmd_path = ft_strdup(shell->cmd_list->args[0]);
	if (!shell->exec->cmd_path)
		return (0);
	return (1);
}
