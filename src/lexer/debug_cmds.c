/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:07:42 by alexis            #+#    #+#             */
/*   Updated: 2025/07/04 15:18:30 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Get string representation of redirection type
 * @param index: Index of the redirection type
 * @return: String representation
 */
static const char	*get_redir_types(int index)
{
	static const char	*redir_types[] = {
		"UNKNOWN", "WORD", "PIPE", "REDIR IN (<)", "REDIR OUT (>)",
		"REDIR APPEND (>>)", "HEREDOC (<<)", "EOF", "VAR"
	};

	return (redir_types[index]);
}

/**
 * Get string representation of redirection type
 * @param type: Redirection type
 * @return: String representation
 */
static void	print_args(char **args)
{
	int	i;

	if (args)
	{
		printf("  Args: ");
		i = 0;
		while (args[i])
		{
			printf("'%s' ", args[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("  No args\n");
}

/**
 * Get string representation of redirection type
 * @param type: Redirection type
 * @return: String representation
 */
static void	print_assignments(t_assignment *assignments)
{
	t_assignment	*assign;

	if (assignments)
	{
		printf("  Assignments:\n");
		assign = assignments;
		while (assign)
		{
			printf("    %s = %s\n", assign->key, assign->value);
			assign = assign->next;
		}
	}
}

/**
 * Get string representation of redirection type
 * @param type: Redirection type
 * @return: String representation
 */
static void	print_redirections(t_redir *redirections)
{
	t_redir	*redir;

	if (redirections)
	{
		printf("  Redirections:\n");
		redir = redirections;
		while (redir)
		{
			printf("    %s -> '%s'", get_redir_types(redir->type), redir->file);
			if (redir->fd != -1)
				printf(" (fd: %d)", redir->fd);
			printf("\n");
			redir = redir->next;
		}
	}
}

/**
 * Debug function to print command structure
 * @param commands: Head of command list
 */
void	print_commands(t_cmd *commands)
{
	t_cmd	*current;
	int		cmd_num;

	current = commands;
	cmd_num = 1;
	printf("=== COMMANDS ===\n");
	while (current)
	{
		printf("Command %d:\n", cmd_num);
		print_args(current->args);
		print_assignments(current->assignments);
		print_redirections(current->redirections);
		if (current->next)
			printf("  -> PIPE TO NEXT COMMAND\n");
		printf("\n");
		current = current->next;
		cmd_num++;
	}
	printf("================\n");
}
