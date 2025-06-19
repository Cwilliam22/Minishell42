/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:42:25 by alfavre           #+#    #+#             */
/*   Updated: 2025/06/19 15:42:42 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(char *token)
{
	printf("minishell: syntax error near unexpected token `%s'\n", token);
}

void	print_error(char *cmd, char *arg, char *msg)
{
	printf("minishell: ");
	if (cmd)
		printf("%s: ", cmd);
	if (arg)
		printf("%s: ", arg);
	if (msg)
		printf("%s", msg);
	printf("\n");
}
