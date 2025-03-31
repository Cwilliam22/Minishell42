/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:11:44 by alfavre           #+#    #+#             */
/*   Updated: 2025/03/31 14:31:49 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
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

t_token	*tokenize(char *input);
void	free_token_list(t_token *head);

char	*skip_spaces(char *str);
char	*extract_word(char *str, int *pos);
char	*handle_quotes(char *str, int *pos, char quote_type);
int		is_operator_char(char c);
t_token	*create_operator_token(char *str, int *pos);
t_token	*add_token(t_token **head, t_token_type type, char *value);

#endif