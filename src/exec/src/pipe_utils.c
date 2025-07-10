/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 00:29:00 by alexis            #+#    #+#             */
/*   Updated: 2025/07/10 00:32:29 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_pipes(int **pipes, t_exec *exec)
{
	int	j;

	j = 0;
	while (j < exec->nbr_pipes)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	return (1);
}

