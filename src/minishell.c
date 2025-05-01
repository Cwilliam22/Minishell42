/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:30:39 by alfavre           #+#    #+#             */
/*   Updated: 2025/05/01 14:50:14 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*init_shell_env(char **envp)
{
	t_env	*env;

	env = NULL;
	env = init_env(envp);
	if (!env)
		return (NULL);
	retrun (env);
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

	status = 0;
	while (1)
	{
		setup_signals();
		input = get_input();
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		cmd_list = parse(, &status);
		if (cmd_list)
			status = exe
	}
}