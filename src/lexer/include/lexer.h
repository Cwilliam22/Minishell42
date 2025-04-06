/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:11:44 by alfavre           #+#    #+#             */
/*   Updated: 2025/04/06 10:06:39 by alexis           ###   ########.fr       */
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
	TOKEN_WORD,					// Simple word, command, arguments
	TOKEN_PIPE,					// |
	TOKEN_REDIR_IN,				// <
	TOKEN_REDIR_OUT,			// >
	TOKEN_APPEND,				// >>
	TOKEN_HEREDOC,				// <<
	TOKEN_OPEN_PARENTHESES,		// (
	TOKEN_CLOSE_PARENTHESES,	// )
	TOKEN_EOF					// End of line
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
	struct t_command	*next;
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

/*Parsing functions*/
t_command	*parse(t_token *tokens, t_env *env);
void		free_commands(t_command *cmd);

/*Utils functions*/
int		is_whitespace(char c);
int		is_special_char(char c);

#endif