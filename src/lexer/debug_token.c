/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:35:32 by alexis            #+#    #+#             */
/*   Updated: 2025/07/04 15:18:37 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Debug function to print tokens
 * @param tokens: Head of token list
 */
void	print_tokens(t_token *tokens)
{
	t_token		*current;
	const char	*type_names[] = {
		"UNKNOWN", "WORD", "PIPE", "REDIR_IN",
		"REDIR_OUT", "REDIR_APPEND", "HEREDOC", "EOF", "VAR"
	};

	current = tokens;
	printf("=== TOKENS ===\n");
	while (current)
	{
		printf("Type: %-12s Value: '%s'\n",
			type_names[current->type], current->value);
		current = current->next;
	}
	printf("==============\n");
}
