/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:17:28 by alexis            #+#    #+#             */
/*   Updated: 2025/07/04 14:33:31 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if a string needs variable expansion.
 * @param str The string to check.
 * @return 1 if the string starts with '$' and is not empty, 0 otherwise.
 */
int	needs_expansion(char *str)
{
	return (str && str[0] == '$' && str[1] != '\0');
}

/**
 * @brief Expand all commands in the command list.
 * @param commands The list of commands to expand.
 * @param shell The shell context containing environment variables.
 */
void	expand_commands(t_cmd *commands, t_shell *shell)
{
	t_cmd	*current;

	current = commands;
	while (current)
	{
		expand_command_args(current, shell);
		current = current->next;
	}
}

/**
 * @brief Expand variables in a command's arguments.
 * @param cmd The command whose arguments will be expanded.
 * @param shell The shell context containing environment variables.
 */
void	expand_command_args(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args[i])
	{
		if (needs_expansion(cmd->args[i]))
		{
			expanded = expand_variables(cmd->args[i], shell);
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}
