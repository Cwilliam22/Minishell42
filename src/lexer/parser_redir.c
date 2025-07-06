/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:51:17 by alexis            #+#    #+#             */
/*   Updated: 2025/07/04 16:16:49 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Extract redirections from token list
 * @param tokens: Starting token
 * @param cmd: Command to fill
 * @return: 1 on success, 0 on error
 */
int	extract_redirections(t_token *tokens, t_cmd *cmd)
{
	t_token	*current;
	t_redir	*redir;
	char	*filename;

	current = tokens;
	while (current && current->type != TOKEN_PIPE)
	{
		if (current->type >= TOKEN_REDIR_IN && current->type <= TOKEN_HEREDOC)
		{
			if (!current->next || current->next->type != TOKEN_WORD)
				return (0);
			filename = handle_quotes(current->next->value, NULL);
			if (!filename)
				return (0);
			redir = create_redirection(current->type, filename);
			free(filename);
			if (!redir)
				return (0);
			add_redirection(&cmd->redirections, redir);
			current = current->next;
		}
		current = current->next;
	}
	return (1);
}
