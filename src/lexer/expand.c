/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:17:28 by alexis            #+#    #+#             */
/*   Updated: 2025/07/02 21:20:51 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int needs_expansion(char *str)
{
	return (str && str[0] == '$' && str[1] != '\0');
}

void expand_commands(t_cmd *commands, t_shell *shell)
{
	t_cmd *current = commands;

	while (current)
	{
		expand_command_args(current, shell);
		current = current->next;
	}
}

void expand_command_args(t_cmd *cmd, t_shell *shell)
{
	int i = 0;

	while (cmd->args[i])
	{
		if (needs_expansion(cmd->args[i])) // Vérifie si contient $
		{
			char *expanded = expand_variables(cmd->args[i], shell);
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}