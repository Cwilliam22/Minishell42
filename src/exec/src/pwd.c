/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:11:50 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/09 14:10:48 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_shell *shell)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (0);
	printf("%s\n", path);
	free(shell->exec->oldpwd);
	free(path);
	return (0);
}
