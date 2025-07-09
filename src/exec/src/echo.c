/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:18:37 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/09 14:08:34 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_printf_arg(char **tab_arg, int index, int option, t_shell *shell)
{
	int	i;

	(void)shell;
	i = index;
	while (tab_arg[i])
	{
		ft_printf("%s", tab_arg[i]);
		if (tab_arg[i + 1])
			ft_printf(" ");
		i++;
	}
	if (option == 0)
		ft_printf("\n");
	return (1);
}

int	builtin_echo(t_shell *shell)
{
	int		i;
	char	**arg;

	i = 1;
	arg = shell->cmd_list->args;
	if (arg[1] == NULL)
	{
		ft_printf("\n");
		return (0);
	}
	else if (ft_strncmp("-n", arg[1], 2) == 0)
	{
		i = skip_n(arg);
		if (i == -1)
			return (1);
		if (!ft_printf_arg(arg, i, 1, shell))
			return (1);
	}
	else
	{
		if (!ft_printf_arg(arg, i, 0, shell))
			return (1);
	}
	return (0);
}
