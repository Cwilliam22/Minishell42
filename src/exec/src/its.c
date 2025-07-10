/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:23:48 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/09 23:25:26 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
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
