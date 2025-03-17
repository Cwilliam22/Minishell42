/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:04:08 by alfavre           #+#    #+#             */
/*   Updated: 2025/03/16 14:59:16 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	main(int argc, char **argv)
{
	char	*input;
	char	**token;

	(void)argc;
	(void)argv;
	input = readline("Entrer une commande: ");
	if (input && *input)
		add_history(input);
	token = ft_split(input, ' ');
	while (*token)
		ft_printf("Vous avez entre : %s\n", *(token++));
	free(input);
	return (0);
}
