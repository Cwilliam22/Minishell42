/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_v1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:57:44 by root              #+#    #+#             */
/*   Updated: 2025/06/09 14:44:06 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_v1.h"

/* Global variable for signal handling (only signal number allowed) */
int	g_signal_received = 0;

/**
 * Initialize the shell structure with environment variables
 * @param shell: Shell structure to initialize
 * @param envp: Environment variables from main
 */
static void	init_shell(t_shell *shell, char **envp)
{
	shell->env_list = NULL;
	shell->env_array = NULL;
	shell->cmd_list = NULL;
	shell->token_list = NULL;
	shell->exit_status = 0;
	shell->in_heredoc = 0;
	shell->input_line = NULL;
	
	/* Initialize environment variables */
	init_env_list(shell, envp);
	shell->env_array = env_list_to_array(shell->env_list);
	
	/* Set up signal handlers */
	setup_signals();
}

/**
 * Clean up and free all shell resources
 * @param shell: Shell structure to clean up
 */
static void	cleanup_shell(t_shell *shell)
{
	if (shell->input_line)
	{
		free(shell->input_line);
		shell->input_line = NULL;
	}
	if (shell->token_list)
	{
		free_tokens(shell->token_list);
		shell->token_list = NULL;
	}
	if (shell->cmd_list)
	{
		free_commands(shell->cmd_list);
		shell->cmd_list = NULL;
	}
	if (shell->env_list)
	{
		free_env_list(shell->env_list);
		shell->env_list = NULL;
	}
	if (shell->env_array)
	{
		free_env_array(shell->env_array);
		shell->env_array = NULL;
	}
}

/**
 * Process a single line of input
 * @param shell: Shell structure
 * @param input: Input line to process
 * @return: 1 to continue, 0 to exit
 */
static int	process_input(t_shell *shell, char *input)
{
	/* Skip empty lines */
	if (!input || !*input || ft_strlen(input) == 0)
		return (1);
	
	/* Add to history if not empty */
	add_history(input);
	
	/* Store input line in shell structure */
	shell->input_line = ft_strdup(input);
	if (!shell->input_line)
	{
		print_error("minishell", NULL, "malloc failed");
		return (1);
	}
	
	/* Tokenize the input */
	shell->token_list = tokenize(shell->input_line);
	if (!shell->token_list)
	{
		free(shell->input_line);
		shell->input_line = NULL;
		return (1);
	}

	print_tokens(shell->token_list);
	
	/* Check syntax errors */
	if (!check_syntax(shell->token_list))
	{
		shell->exit_status = 2;
		free_tokens(shell->token_list);
		shell->token_list = NULL;
		free(shell->input_line);
		shell->input_line = NULL;
		return (1);
	}
	
	/* Parse tokens into commands */
	shell->cmd_list = parse_tokens(shell->token_list, shell);
	if (!shell->cmd_list)
	{
		free_tokens(shell->token_list);
		shell->token_list = NULL;
		free(shell->input_line);
		shell->input_line = NULL;
		return (1);
	}
	
	print_commands(shell->cmd_list);

	/* Execute the command pipeline */
	shell->exit_status = ft_exec(shell, exec); // Again 
	
	/* Check if we should exit */
	if (shell->exit_status == -1)
	{
		/* Clean up for next iteration */
		free_commands(shell->cmd_list);
		shell->cmd_list = NULL;
		free_tokens(shell->token_list);
		shell->token_list = NULL;
		free(shell->input_line);
		shell->input_line = NULL;
		return (0); /* Signal to exit */
	}
	
	/* Clean up for next iteration */
	free_commands(shell->cmd_list);
	shell->cmd_list = NULL;
	free_tokens(shell->token_list);
	shell->token_list = NULL;
	free(shell->input_line);
	shell->input_line = NULL;
	
	return (1);
}

/**
 * Main shell loop - REPL (Read-Eval-Print Loop)
 * @param shell: Shell structure
 */
static void	shell_loop(t_shell *shell)
{
	char	*input;
	int		continue_loop;

	continue_loop = 1;
	while (continue_loop)
	{
		/* Reset signal flag */
		g_signal_received = 0;
		
		/* Read input from user */
		input = readline(PROMPT);
		
		/* Handle EOF (ctrl-D) */
		if (!input)
		{
			printf("exit\n");
			break;
		}
		
		/* Handle signal interruption */
		if (g_signal_received == SIGINT)
		{
			shell->exit_status = 130;
			free(input);
			continue;
		}
		
		/* Process the input */
		continue_loop = process_input(shell, input);
		
		/* Free the input line */
		free(input);
	}
}

/**
 * Handle command line arguments
 * @param argc: Argument count
 * @param argv: Argument vector
 * @return: 0 if valid, 1 if error
 */
static int	handle_arguments(int argc, char **argv)
{
	if (argc > 1)
	{
		if (argv[1][0] == '-' && argv[1][1] == 'c')
		{
			print_error("minishell", "-c", "option not supported");
			return (1);
		}
		else
		{
			print_error("minishell", argv[1], "no such file or directory");
			return (1);
		}
	}
	return (0);
}

/**
 * Print welcome message
 */
static void	print_welcome(void)
{
	printf("\n");
	printf("╔══════════════════════════════════════╗\n");
	printf("║           🐚 MINISHELL 🐚            ║\n");
	printf("║                                      ║\n");
	printf("║      A beautiful shell experience    ║\n");
	printf("║                                      ║\n");
	printf("║  Type 'exit' to quit                 ║\n");
	printf("║  Use ctrl-C, ctrl-D as in bash       ║\n");
	printf("╚══════════════════════════════════════╝\n");
	printf("\n");
}

/**
 * Main function - entry point of minishell
 * @param argc: Argument count
 * @param argv: Argument vector
 * @param envp: Environment variables
 * @return: Exit status
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		exit_status;

	/* Handle command line arguments */
	if (handle_arguments(argc, argv))
		return (1);
	
	/* Initialize shell */
	init_shell(&shell, envp);
	
	/* Print welcome message only in interactive mode */
	if (isatty(STDIN_FILENO))
		print_welcome();
	
	/* Main shell loop */
	shell_loop(&shell);
	
	/* Store exit status before cleanup */
	exit_status = shell.exit_status;
	
	/* Cleanup and exit */
	cleanup_shell(&shell);
	rl_clear_history();
	
	return (exit_status);
}