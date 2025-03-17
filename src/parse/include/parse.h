/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:11:44 by alfavre           #+#    #+#             */
/*   Updated: 2025/03/17 15:49:43 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/include/libft.h"

typedef enum e_token_type
{
	TOKEN_WORD,					// Simple word, command, arguments
	TOKEN_PIPE,					// |
	TOKEN_REDIR_IN,				// <
	TOKEN_REDIR_OUT,			// >
	TOKEN_APPEND,				// >>
	TOKEN_HEREDOC,				// <<
	TOKEN_AND,					// &&
	TOKEN_OR,					// ||
	TOKEN_SEMICOLON,			// ;
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

#endif