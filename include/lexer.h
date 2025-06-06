/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:11:44 by alfavre           #+#    #+#             */
/*   Updated: 2025/05/27 08:02:23 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include "../src/lexer/libft/include/libft.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef enum	e_parse_result
{
	PARSE_OK,
	PARSE_ERROR_SYNTAX,
	PARSE_ERROR_QUOTE,
	PARSE_ERROR_PIPE,
	PARSE_ERROR_REDIRECTION
}	t_parse_result;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				*name;
	char				**args;
	t_redir				*redirections;
	struct s_command	*next;
}	t_command;

/*Tokinization functions*/
t_token		*tokenize(char *input);
void		free_tokens(t_token *tokens);

/*Token utils functions*/
int			is_whitespace(char c);
char		*extract_word(char *input, int *i);

/*Parsing functions*/
t_command	*parse(t_token *tokens, int last_exit_code);

/*Parse utils functions*/
t_command	*new_command(void);
t_redir		*new_redirection(t_token_type type, char *file);
void		add_redirection(t_command *cmd, t_redir *new);
int			count_args(t_token *tokens);
char		**extract_args(t_token **tokens, int arg_count);

/*Parse free functions*/
void		free_redirection(t_redir *redirections);
void		free_command(t_command *cmd);
void		free_commands(t_command *cmd);

/*Debug functions*/
void		print_token(t_token *token);
void		print_all_tokens(t_token *tokens);
void		print_redirection(t_redir *redir);
void		print_command(t_command *cmd);
void		print_all_commands(t_command *cmd);

/*Check error*/
t_parse_result	validate_syntax(char *input);

#endif