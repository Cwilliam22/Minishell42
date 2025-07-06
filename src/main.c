/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:57:44 by root              #+#    #+#             */
/*   Updated: 2025/07/06 16:23:01 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_shlvl(t_exec *exec)
{
	int		shlvl;
	int		place;
	char	*new_lvl;

	place = find_sth_in_env("SHLVL", exec->env);
	if (place == -1)
		return (0);
	shlvl = ft_atoi(find_value_in_env("SHLVL", exec));
	shlvl++;
	free(exec->env[place][1]);
	new_lvl = ft_itoa(shlvl);
	exec->env[place][1] = ft_strdup(new_lvl);
	free(new_lvl);
	return (1);
}

int	ft_env(char **envp, t_exec *exec)
{
	if (!copy_env1(envp, exec))
		return (0);
	if (!ft_shlvl(exec))
		return (0);
	if (!exec->env)
		return (0);
	exec->nbr_var_env = ft_envlen(exec->env);
	return (1);
}

/**
 * Initialize the shell structure with environment variables
 * @param shell: Shell structure to initialize
 * @param envp: Environment variables from main
 */
static void	init_shell(t_shell *shell, char **envp, t_exec *exec)
{
	shell->cmd_list = NULL;
	shell->token_list = NULL;
	shell->exit_status = 0;
	shell->in_heredoc = 0;
	shell->input_line = NULL;
	init_all(exec);
	exec->env = NULL;
	exec->out = 0;
	ft_env(envp, exec);
	shell->exec = exec;
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
}

/**
 * Process a single line of input
 * @param shell: Shell structure
 * @param input: Input line to process
 * @return: 1 to continue, 0 to exit
 */
static int	process_input(t_shell *shell, char *input)
{
	int	exec_result;
	int	signal_exit_code;
	int	error;

	if (!input || !*input || ft_strlen(input) == 0)
		return (1);
	add_history(input);
	shell->input_line = ft_strdup(input);
	if (!shell->input_line)
	{
		print_error("minishell", NULL, "malloc failed");
		return (1);
	}
	shell->token_list = tokenize(shell->input_line);
	if (!shell->token_list)
	{
		free(shell->input_line);
		shell->input_line = NULL;
		return (1);
	}
	//print_tokens(shell->token_list);
	error = check_token_syntax(shell->token_list);
	if (error != 1)
	{
		shell->exit_status = 2;
		free_tokens(shell->token_list);
		shell->token_list = NULL;
		free(shell->input_line);
		shell->input_line = NULL;
		return (1);
	}
	shell->cmd_list = parse_tokens(shell->token_list, shell);
	if (!shell->cmd_list)
	{
		free_tokens(shell->token_list);
		shell->token_list = NULL;
		free(shell->input_line);
		shell->input_line = NULL;
		return (1);
	}
	//print_commands(shell->cmd_list);
	exec_result = ft_exec(shell);
	if (shell->exec->exit == 1)
	{
		free_commands(shell->cmd_list);
		shell->cmd_list = NULL;
		free_tokens(shell->token_list);
		shell->token_list = NULL;
		free(shell->input_line);
		shell->input_line = NULL;
		return (0);
	}
	signal_exit_code = check_and_handle_signal();
	if (signal_exit_code != 0)
		shell->exit_status = signal_exit_code;
	else
		shell->exit_status = exec_result;
	if (exec_result == -1)
	{
		free_commands(shell->cmd_list);
		shell->cmd_list = NULL;
		free_tokens(shell->token_list);
		shell->token_list = NULL;
		free(shell->input_line);
		shell->input_line = NULL;
		return (0);
	}
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
	int		signal_exit_code;

	continue_loop = 1;
	setup_interactive_signals();
	while (continue_loop)
	{
		g_signal_received = 0;
		setup_interactive_signals();
		input = readline(PROMPT);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		signal_exit_code = check_and_handle_signal();
		if (signal_exit_code != 0)
		{
			shell->exit_status = signal_exit_code;
			free(input);
			break ;
		}
		continue_loop = process_input(shell, input);
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
	t_exec	exec;

	if (handle_arguments(argc, argv))
		return (1);
	init_shell(&shell, envp, &exec);
	if (isatty(STDIN_FILENO))
		print_welcome();
	shell_loop(&shell);
	shell.exit_status = shell.exec->out;
	cleanup_shell(&shell);
	rl_clear_history();
	return (shell.exit_status);
}
