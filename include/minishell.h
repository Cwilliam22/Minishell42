#ifndef MINISHELL_H
# define MINISHELL_H

# include "exec.h"
# include "lexer.h"

# include <stdlib.h>
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

extern int	g_exit_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env		*shell;
	t_command	*cmd;
	char		*line;
	int			last_exit_code;
}	t_shell;

// main.c


#endif