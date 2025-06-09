
#include "../../../include/exec.h"
#include "../../../include/lexer.h"

/*
void	init_all(t_exec *exec)
{
	exec->args = NULL;
	exec->line = 0;
	exec->cmd_path = NULL;
	exec->path = NULL;
	exec->fd_in = 0;
	exec->fd_out = 0;
	exec->nbr_process = 0;
	exec->nbr_pipes = 0;
	exec->nbr_var_env = 0;
	exec->nbr_arg = 0;
	exec->cmd = NULL;
	exec->out = 0;
	exec->is_pipe = 0;
}

int ft_exec(, t_exec *exec)
{
	init_all(exec); // init variables
	if (!copy_env1(envp, exec)) // copy env in a variable env
		return (1);
	if (!exec->env) // security
		return (1);
	exec->nbr_var_env = ft_envlen(exec.env);
	exec->nbr_process = ft_lstlen(cmd_list);
	exec->nbr_pipes = exec->nbr_process - 1;
	exec->path = ft_strdup(exec->env[find_var_path(exec->env)][1]);
	if (exec->nbr_process == 1) // if the cmd is not a pipeline
	{
		if (!identification(cmd_list, exec))
			return (ft_printf("Not a command valid\n"), 1);
	}
	else if (exec->nbr_process > 1) // if the cmd is a pipeline
	{
		printf("It's a pipeline !!\n");
		if (!pipeline(cmd_list, exec))
			return (ft_printf("Not a command valid\n"), 1);
	}
	free_var(exec);
	free_all_env(exec);
	return (0);
}
*/


t_command	*create_test_command(void)
{
	t_command	*cmd1 = malloc(sizeof(t_command));
	t_command	*cmd2 = malloc(sizeof(t_command));

	// cmd1 echo test
	cmd1->name = ft_strdup("echo");
	cmd1->args = malloc(sizeof(char *) * 3);
	cmd1->args[0] = ft_strdup("echo");
	cmd1->args[1] = ft_strdup("test");
	cmd1->args[2] = NULL;
	cmd1->redirections = NULL;
	cmd1->next = cmd2;

	// cmd2 : wc -l
	cmd2->name = ft_strdup("wc");
	cmd2->args = malloc(sizeof(char *) * 3);
	cmd2->args[0] = ft_strdup("wc");
	cmd2->args[1] = ft_strdup("-l");
	cmd2->args[2] = NULL;
	cmd2->redirections = NULL;
	cmd2->next = NULL;

	return cmd1;
}

/*
t_command	*create_test_command(void)
{
	t_command	*cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);

	cmd->name = ft_strdup("ls");
	cmd->args = malloc(sizeof(char *) * 2);
	if (!cmd->args)
		return (NULL);

	cmd->args[0] = ft_strdup("ls");
	cmd->args[1] = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;

	return cmd;
}
*/

void	init_all(t_exec *exec)
{
	exec->args = NULL; //
	exec->env = NULL; // 1
	exec->cmd_path = NULL; // 0
	exec->path = NULL; // 1
	exec->fd_in = 0; //
	exec->fd_out = 0; //
	exec->nbr_process = 0; // 1
	exec->nbr_pipes = 0; // 1
	exec->nbr_var_env = 0; // 1
	exec->nbr_arg = 0; // 1
	exec->cmd = NULL; //
	exec->out = 0; //
	exec->is_pipe = 0; //
}


int	main(int argc, char **argv, char **envp)
{
	t_exec exec;

	(void)argc;
	(void)argv;
	t_command *cmd_list = create_test_command();
	init_all(&exec);
	if (!copy_env1(envp, &exec))
		return (1);
	if (!exec.env)
		return (1);
	exec.nbr_var_env = ft_envlen(exec.env);
	exec.nbr_process = ft_lstlen(cmd_list);
	exec.nbr_pipes = exec.nbr_process - 1;
	exec.path = ft_strdup(exec.env[find_var_path(exec.env)][1]);
	if (exec.nbr_process == 1)
	{
		if (!identification(cmd_list, &exec))
			return (ft_printf("Not a command valid\n"), 1);
	}
	else if (exec.nbr_process > 1)
	{
		printf("It's a pipeline !!\n");
		if (!pipeline(cmd_list, &exec))
			return (ft_printf("Not a command valid\n"), 1);
	}
	free_var(&exec);
	free_all_env(&exec);
	return (0);
}

