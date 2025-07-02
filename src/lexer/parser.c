/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:31:41 by root              #+#    #+#             */
/*   Updated: 2025/07/02 22:17:08 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Create a new command structure
 * @return: New command or NULL on error
 */
t_cmd	*create_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->assignments = NULL;
	cmd->redirections = NULL;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->pid = -1;
	cmd->next = NULL;
	return (cmd);
}

/**
 * Add command to the end of the list
 * @param head: Pointer to the head of the command list
 * @param new_cmd: Command to add
 */
void	add_command(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!head || !new_cmd)
		return ;
	if (!*head)
	{
		*head = new_cmd;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

/**
 * Free all commands in the list
 * @param commands: Head of the command list
 */
void	free_commands(t_cmd *commands)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	current = commands;
	while (current)
	{
		next = current->next;
		
		/* Free arguments array */
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				free(current->args[i]);
				i++;
			}
			free(current->args);
		}
		
		/* Free assignments */
		free_assignments(current->assignments);
		
		/* Free redirections */
		free_redirections(current->redirections);
		
		free(current);
		current = next;
	}
}

/**
 * Check syntax errors in token list
 * @param tokens: Head of token list
 * @return: 1 if syntax is valid, the value of the synthax error otherwise
 */
int	check_token_syntax(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (1);
	current = tokens;
	/* Check for pipe at the beginning */
	if (current->type == TOKEN_PIPE)
	{
		print_syntax_error("|");
		return (2);
	}
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			/* Check for consecutive pipes or pipe at end */
			if (!current->next || current->next->type == TOKEN_PIPE)
			{
				print_syntax_error("|");
				return (2);
			}
		}
		else if (current->type >= TOKEN_REDIR_IN && current->type <= TOKEN_HEREDOC)
		{
			/* Redirection must be followed by a word */
			if (!current->next || current->next->type != TOKEN_WORD)
			{
				if (current->next)
					print_syntax_error(current->next->value);
				else
					print_syntax_error("newline");
				return (2);
			}
		}
		current = current->next;
	}
	return (1);
}

/**
 * Count word tokens in current command (until pipe)
 * @param tokens: Starting token
 * @return: Number of word tokens
 */
static int	count_words(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 0;
	
	while (current && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_WORD || current->type == TOKEN_VAR)
		{
			count++;
		}
		else if (current->type >= TOKEN_REDIR_IN && current->type <= TOKEN_HEREDOC)
		{
			// Skip redirection and its target
			if (current->next)
				current = current->next; // Skip the target
		}
		current = current->next;
	}
	
	return (count);
}

/**
 * Extract arguments from token list
 * @param tokens: Starting token
 * @param cmd: Command to fill
 * @return: 1 on success, 0 on error
 */
static int	extract_arguments(t_token *tokens, t_cmd *cmd, t_shell *shell)
{
	t_token	*current;
	int		word_count;
	int		i;

	word_count = count_words(tokens);
	if (word_count == 0)
	{
		cmd->args = NULL;
		return (1);
	}
	
	cmd->args = malloc(sizeof(char *) * (word_count + 1));
	if (!cmd->args)
		return (0);
	
	current = tokens;
	i = 0;
	
	while (current && current->type != TOKEN_PIPE && i < word_count)
	{
		if (current->type == TOKEN_WORD || current->type == TOKEN_VAR)
		{
			if (current->type == TOKEN_VAR)
				cmd->args[i] = expand_variables(current->value, shell);
			else
				cmd->args[i] = handle_quotes(current->value, shell);
			if (!cmd->args[i])
			{
				while (--i >= 0)
					free(cmd->args[i]);
				free(cmd->args);
				cmd->args = NULL;
				return (0);
			}
			i++;
		}
		else if (current->type >= TOKEN_REDIR_IN && current->type <= TOKEN_HEREDOC)
		{
			// Skip redirection and its target
			if (current->next)
				current = current->next;
		}
		current = current->next;
	}
	
	cmd->args[i] = NULL;
	return (1);
}

/**
 * Extract redirections from token list
 * @param tokens: Starting token
 * @param cmd: Command to fill
 * @return: 1 on success, 0 on error
 */
static int	extract_redirections(t_token *tokens, t_cmd *cmd)
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
			
			/* Skip the target token */
			current = current->next;
		}
		
		current = current->next;
	}
	
	return (1);
}

/**
 * Parse a single command from tokens
 * @param tokens: Starting token for this command
 * @return: Command structure or NULL on error
 */
static t_cmd	*parse_single_command(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmd;

	if (!tokens)
		return (NULL);
	
	if (strcmp(tokens->value, "$?") == 0)
	{
		free(tokens->value);
		tokens->value = ft_itoa(shell->exit_status);
	}
	cmd = create_command();
	if (!cmd)
		return (NULL);
	
	/* Extract arguments */
	if (!extract_arguments(tokens, cmd, shell))
	{
		free_commands(cmd);
		return (NULL);
	}
	
	/* Extract redirections */
	if (!extract_redirections(tokens, cmd))
	{
		free_commands(cmd);
		return (NULL);
	}
	
	return (cmd);
}

/**
 * Split token list by pipes
 * @param tokens: Head of token list
 * @return: Array of token lists (one per command)
 */
static t_token	**split_by_pipes(t_token *tokens)
{
	t_token	**commands;
	t_token	*current;
	int		pipe_count;
	int		i;

	if (!tokens)
		return (NULL);
	
	/* Count pipes to determine number of commands */
	current = tokens;
	pipe_count = 0;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			pipe_count++;
		current = current->next;
	}
	
	/* Allocate array for commands + 1 (last command) + 1 (NULL terminator) */
	commands = malloc(sizeof(t_token *) * (pipe_count + 2));
	if (!commands)
		return (NULL);
	
	/* Fill the array */
	current = tokens;
	i = 0;
	commands[i] = current;
	
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			i++;
			commands[i] = current->next;
			current = current->next;
		}
		else
			current = current->next;
	}
	commands[i + 1] = NULL;
	return (commands);
}

/**
 * Main parsing function - converts tokens to command list
 * @param tokens: Head of token list
 * @param shell: Shell structure
 * @return: Head of command list or NULL on error
 */
t_cmd	*parse_tokens(t_token *tokens, t_shell *shell)
{
	t_cmd		*head;
	t_cmd		*cmd;
	t_token		**cmd_tokens;
	int			i;

	if (!tokens)
		return (NULL);
	
	/* Split tokens by pipes */
	cmd_tokens = split_by_pipes(tokens);
	if (!cmd_tokens)
		return (NULL);
	
	head = NULL;
	i = 0;
	
	/* Parse each command */
	while (cmd_tokens[i])
	{
		cmd = parse_single_command(cmd_tokens[i], shell);
		if (!cmd)
		{
			free_commands(head);
			free(cmd_tokens);
			return (NULL);
		}
		add_command(&head, cmd);
		i++;
	}
	
	free(cmd_tokens);
	return (head);
}

/**
 * Debug function to print commands
 * @param commands: Head of command list
 */
void	print_commands(t_cmd *commands)
{
	t_cmd			*current;
	t_assignment	*assign;
	t_redir			*redir;
	int				i;
	int				cmd_num;
	const char		*redir_types[] = {
		"UNKNOWN", "WORD", "PIPE", "INPUT (<)", 
		"OUTPUT (>)", "APPEND (>>)", "HEREDOC (<<)", "EOF"
	};

	current = commands;
	cmd_num = 1;
	printf("=== COMMANDS ===\n");
	while (current)
	{
		printf("Command %d:\n", cmd_num);
		if (current->args)
		{
			printf("  Args: ");
			i = 0;
			while (current->args[i])
			{
				printf("'%s' ", current->args[i]);
				i++;
			}
			printf("\n");
		}
		else
			printf("  No args\n");
		if (current->assignments)
		{
			printf("  Assignments:\n");
			assign = current->assignments;
			while (assign)
			{
				printf("    %s = %s\n", assign->key, assign->value);
				assign = assign->next;
			}
		}
		if (current->redirections)
		{
			printf("  Redirections:\n");
			redir = current->redirections;
			while (redir)
			{
				printf("    %s -> '%s'", redir_types[redir->type], redir->file);
				if (redir->fd != -1)
					printf(" (fd: %d)", redir->fd);
				printf("\n");
				redir = redir->next;
			}
		}
		if (current->next)
			printf("  -> PIPE TO NEXT COMMAND\n");
		printf("\n");
		current = current->next;
		cmd_num++;
	}
	printf("================\n");
}
