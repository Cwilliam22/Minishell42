
#include "../include/minishell.h"

static t_env	*init_shell_env(char **envp)
{
	t_env	*env;

	env = NULL;
	env = init_env(envp);
	if (!env)
		return (NULL);
	return (env);
}

int ft_env(char **envp, t_exec *exec)
{
    if (!copy_env1(envp, exec))
		return (0);
    if (!exec->env)
		return (0);
    exec->nbr_var_env = ft_envlen(exec->env);
    return (1);
}

static char	*get_input(void)
{
	char	*input;
	char	*prompt;

	prompt = generate_prompt();
	input = readline(prompt);
	free(prompt);
	if (input && *input)
		add_history(input);
	return (input);
}

static void	shell_loop(t_env *env)
{
	char		*input;
	t_command	*cmd_list;
	int			status;
	t_token		*tokens;

	status = 0;
	while (1)
	{
		//setup_signals();
		input = get_input();
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		tokens = tokenize(input);
		cmd_list = NULL;
		if (tokens)
		{
			cmd_list = parse(tokens, status);
			free_tokens(tokens);
		}
		if (cmd_list)
			status = execute_commands(cmd_list, env);
		free(input);
		if (cmd_list)
			free_commands(cmd_list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	//rl_catch_signals = 0;
	env = init_shell_env(envp);
	if (!env)
	{
		ft_putendl_fd("Minishell: Failed to initialize environment", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	shell_loop(env);
	free_env(env);
	rl_clear_history();
	return (g_exit_status);
}
