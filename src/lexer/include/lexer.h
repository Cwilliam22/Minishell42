/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:11:44 by alfavre           #+#    #+#             */
/*   Updated: 2025/04/14 11:48:12 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include "../libft/include/libft.h"

typedef enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct	s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct	s_command
{
	char				*name;
	char				**args;
	t_redir				*redirections;
	struct s_command	*next;
}	t_command;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_shell
{
	t_env		*shell;
	t_command	*cmd;
	char		*line;
	int			last_exit_code;
}	t_shell;

/*Tokinization functions*/
t_token	*tokenize(char *input);
void	free_tokens(t_token *tokens);

/*Token utils functions*/
int		is_whitespace(char c);
char	*extract_word(char *input, int *i);

/*Parsing functions*/
t_command	*parse(t_token *tokens, t_env *env, int last_exit_code);

/*Parse utils functions*/
t_command	*new_command(void);
t_redir	*new_redirection(t_token_type type, char *file);
void	add_redirection(t_command *cmd, t_redir *new);
int	count_args(t_token *tokens);
char	**extract_args(t_token **tokens, int arg_count);

/*Parse free functions*/
void	free_redirection(t_redir *redirections);
void	free_command(t_command *cmd);
void	free_commands(t_command *cmd);

/*Debug functions*/
void	print_token(t_token *token);
void	print_all_tokens(t_token *tokens);
void	print_redirection(t_redir *redir);
void	print_command(t_command *cmd);
void	print_all_commands(t_command *cmd);

#endif