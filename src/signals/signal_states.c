/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:36:19 by alfavre           #+#    #+#             */
/*   Updated: 2025/07/13 15:48:11 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Variable globale unique qui encode TOUT l'état des signaux */
int	g_signal_received = 0;

/**
 * Vérifier si un signal a été reçu et retourner son code de sortie
 * @return: Code de sortie approprié (130 pour SIGINT, 131 pour SIGQUIT, 0 sinon)
 */
int	check_and_handle_signal(void)
{
	int	signal_num;
	int	exit_code;

	signal_num = g_signal_received;
	if (signal_num != 0)
		printf("DEBUG: Signal %d reçu\n", signal_num); 
	g_signal_received = 0;
	if (signal_num == SIGINT)
		exit_code = 130;
	else if (signal_num == SIGQUIT)
		exit_code = 131;
	else
		exit_code = 0;
	return (exit_code);
}

/**
 * Vérifier simplement si un signal a été reçu
 * @return: 1 si signal reçu, 0 sinon
 */
int	signal_received(void)
{
	return (g_signal_received != 0);
}

/**
 * Reset la variable globale de signal
 */
void	reset_signal(void)
{
	g_signal_received = 0;
}

/**
 * Obtenir le numéro du signal reçu
 * @return: Numéro du signal ou 0 si aucun
 */
int	get_signal_number(void)
{
	return (g_signal_received);
}
