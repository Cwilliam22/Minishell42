/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 07:53:13 by alfavre           #+#    #+#             */
/*   Updated: 2025/05/27 09:29:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/lexer.h"

// Fonctions utilitaires
static bool is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static char *skip_whitespace(char *str)
{
    while (*str && is_whitespace(*str))
        str++;
    return str;
}

static void print_syntax_error(char *token, int position)
{
    fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n", token);
}

// Vérification des redirections
static t_parse_result check_redirections(char *input)
{
	char *ptr = input;
	bool in_single_quote = false;
	bool in_double_quote = false;

	while (*ptr)
	{
		// Gestion des quotes
		if (*ptr == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*ptr == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote)
		{
			if (*ptr == '>')
			{
				char *next = ptr + 1;
				// Gestion de >>
				if (*next == '>')
					next++;
				// Vérifie qu'il y a un fichier après
				next = skip_whitespace(next);
				if (*next == '\0' || *next == '|' || *next == '>' || *next == '<')
				{
					if (*next == '\0')
						print_syntax_error("newline", next - input);
					else
						print_syntax_error(next, next - input);
					return PARSE_ERROR_REDIRECTION;
				}
			}
			else if (*ptr == '<')
			{
				char *next = skip_whitespace(ptr + 1);
				if (*next == '\0' || *next == '|' || *next == '>' || *next == '<')
				{
					if (*next == '\0')
						print_syntax_error("newline", next - input);
					else
						print_syntax_error(next, next - input);
					return PARSE_ERROR_REDIRECTION;
				}
			}
		}
		ptr++;
	}
	return PARSE_OK;
}

// Vérification des pipes
static t_parse_result check_pipes(char *input)
{
	char *ptr = skip_whitespace(input);
	bool expect_command = true;
	bool in_single_quote = false;
	bool in_double_quote = false;
	char *next;

	// Vérifie si commence par un pipe
	if (*ptr == '|')
		return (print_syntax_error("|", ptr - input), PARSE_ERROR_PIPE);
	while (*ptr)
	{
		// Gestion des quotes
		if (*ptr == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*ptr == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*ptr == '|' && !in_single_quote && !in_double_quote)
		{
			if (expect_command)
				return (print_syntax_error("|", ptr - input), PARSE_ERROR_PIPE);

			// Vérifie les pipes consécutifs
			next = skip_whitespace(ptr + 1);
			if (*next == '|')
				return (print_syntax_error("|", next - input), PARSE_ERROR_PIPE);
			if (*next == '\0')
				return (print_syntax_error("newline", ptr - input + 1), PARSE_ERROR_PIPE);
			expect_command = true;
		}
		else if (!is_whitespace(*ptr) && !in_single_quote && !in_double_quote)
			expect_command = false;
		ptr++;
	}
	return PARSE_OK;
}

// Vérification des quotes
static t_parse_result check_quotes(char *input)
{
	bool in_single_quote = false;
	bool in_double_quote = false;
	char *ptr = input;

	while (*ptr)
	{
		if (*ptr == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*ptr == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		ptr++;
	}
	if (in_single_quote || in_double_quote)
	{
		fprintf(stderr, "minishell: syntax error: unterminated quoted string\n");
		return PARSE_ERROR_QUOTE;
	}
	return PARSE_OK;
}

// Fonction principale de validation
t_parse_result validate_syntax(char *input)
{
	t_parse_result result;

	if (!input || !*input)
		return PARSE_OK;

	// Vérification des quotes
	result = check_quotes(input);
	if (result != PARSE_OK)
		return result;

	// Vérification des pipes
	result = check_pipes(input);
	if (result != PARSE_OK)
		return result;

	// Vérification des redirections
	result = check_redirections(input);
	if (result != PARSE_OK)
		return result;

	return PARSE_OK;
}
