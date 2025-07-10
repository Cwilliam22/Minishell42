/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:11:50 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/10 06:07:18 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_shell *shell)
{
	char	*path;

	if (shell->exec->pwd)
	{
		printf("%s\n", shell->exec->pwd);
		return (0);
	}
	else
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (1);
		printf("%s\n", path);
		free(path);
		return (0);
	}
}
