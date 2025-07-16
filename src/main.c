/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:57:44 by root              #+#    #+#             */
/*   Updated: 2025/07/16 12:33:52 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal_received = 0;

int	ft_shlvl(t_exec *exec)
{
	int		shlvl;
	int		place;
	char	*new_lvl;
	char	*value;
	char	*new_value;

	place = find_sth_in_env("SHLVL", exec->env);
	if (place == -1)
		return (0);
	value = find_value_in_env("SHLVL", exec);
	if (!value)
		return (0);
	shlvl = ft_atoi(value);
	shlvl++;
	free(value);
	new_lvl = ft_itoa(shlvl);
	if (!new_lvl)
		return (0);
	new_value = ft_strdup(new_lvl);
	free(new_lvl);
	if (!new_value)
		return (0);
	free(exec->env[place][1]);
	exec->env[place][1] = new_value;
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
	parent_signal();
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
	if (shell->exec)
	{
		if (shell->exec->path)
		{
			free(shell->exec->path);
			shell->exec->path = NULL;
		}
		if (shell->exec->env)
		{
			free_env(shell->exec);
		}
		if (shell->exec->pwd)
		{
			free(shell->exec->pwd);
			shell->exec->pwd = NULL;
		}
		if (shell->exec->oldpwd)
		{
			free(shell->exec->oldpwd);
			shell->exec->oldpwd = NULL;
		}
	}
	rl_clear_history();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * Helper function to clean up current command resources
 * @param shell: Shell structure to clean
 */
static void	cleanup_current_command(t_shell *shell)
{
	if (shell->cmd_list)
	{
		free_commands(shell->cmd_list);
		shell->cmd_list = NULL;
	}
	if (shell->token_list)
	{
		free_tokens(shell->token_list);
		shell->token_list = NULL;
	}
	if (shell->input_line)
	{
		free(shell->input_line);
		shell->input_line = NULL;
	}
}

/**
 * Initialize command processing - tokenize and parse
 * @param shell: Shell structure
 * @param input: Input string to process
 * @return: 1 on success, 0 on failure
 */
static int	init_command_processing(t_shell *shell, char *input)
{
	shell->input_line = ft_strdup(input);
	if (!shell->input_line)
	{
		print_error("minishell", NULL, "malloc failed");
		return (0);
	}
	shell->token_list = tokenize(shell->input_line);
	if (!shell->token_list)
	{
		cleanup_current_command(shell);
		return (0);
	}
	if (check_token_syntax(shell->token_list) != 1)
	{
		exit_codes(shell, 2, NULL);
		cleanup_current_command(shell);
		return (0);
	}
	shell->cmd_list = parse_tokens(shell->token_list, shell);
	if (!shell->cmd_list)
	{
		cleanup_current_command(shell);
		return (0);
	}
	return (1);
}

/**
 * Handle execution results and signals
 * @param shell: Shell structure
 * @param exec_result: Result from ft_exec
 * @return: 1 to continue, 0 to exit
 */
static int	handle_execution_result(t_shell *shell, int exec_result)
{
	if (shell->exec->exit == 1)
	{
		cleanup_current_command(shell);
		return (0);
	}
	handle_signal(shell);
	if (exec_result == -1)
	{
		cleanup_current_command(shell);
		return (0);
	}
	cleanup_current_command(shell);
	return (1);
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

	if (!input || !*input || ft_strlen(input) == 0)
		return (1);
	add_history(input);
	if (!init_command_processing(shell, input))
		return (1);
	exec_result = ft_exec(shell);
	return (handle_execution_result(shell, exec_result));
}

/**
 * Main shell loop - REPL (Read-Eval-Print Loop)
 * @param shell: Shell structure
 */
static void shell_loop(t_shell *shell)
{
	char	*input;
	int		continue_loop;
	int		result;

	continue_loop = 1;
	while (continue_loop)
	{
		g_signal_received = 0;
		parent_signal();
		input = readline(PROMPT);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		handle_signal(shell);
		result = process_input(shell, input);
		if (result == 0)
			continue_loop = 0;
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
	return (shell.exit_status);
}
