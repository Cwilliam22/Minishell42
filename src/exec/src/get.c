/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:20:34 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/08 14:22:11 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_sth_in_env(char *variable, char ***env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i][0], variable) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*find_value_in_env(char *variable, t_exec *exec)
{
	char	*value;
	int		i;

	i = 0;
	while (ft_strcmp(exec->env[i][0], variable) != 0)
		i++;
	if (ft_strcmp(exec->env[i][0], variable) == 0)
	{
		value = ft_strdup(exec->env[i][1]);
		return (value);
	}
	else
		return (NULL);
}
