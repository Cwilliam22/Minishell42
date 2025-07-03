/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:18:45 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/03 15:05:34 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstlen(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	ft_lstcmdlen(t_assignment *assignment)
{
	int	i;

	i = 0;
	if (!assignment || !assignment->key)
		return (0);
	while (assignment)
	{
		assignment = assignment->next;
		i++;
	}
	return (i);
}

/*
char	**ft_lstcmd_copy(t_cmd *cmd, int index, t_exec *exec)
{
	char	**command;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < index && cmd)
	{
		cmd = cmd->next;
		i++;
	}
	if (!cmd || !cmd->args)
		return (0);
	command = malloc(sizeof(char *) * (ft_lstcmdlen(cmd, index) + 1));
	if (!command)
		return (NULL);
	exec->cmd = ft_strdup(cmd->args[0]);
	while (cmd->args[j])
	{
		command[j] = ft_strdup(cmd->args[j]);
		j++;
	}
	command[j] = NULL;
	return (command);
}
	*/
