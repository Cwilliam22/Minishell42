/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:15:11 by root              #+#    #+#             */
/*   Updated: 2025/06/17 10:56:36 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Create a new token
 * @param value: Token value
 * @param type: Token type
 * @return: New token or NULL on error
 */
t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

/**
 * Add token to the end of the list
 * @param head: Pointer to the head of the token list
 * @param new_token: Token to add
 */
void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

/**
 * Free all tokens in the list
 * @param tokens: Head of the token list
 */
void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

/**
 * Check if character is an operator
 * @param c: Character to check
 * @return: 1 if operator, 0 otherwise
 */
static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * Check if character is whitespace
 * @param c: Character to check
 * @return: 1 if whitespace, 0 otherwise
 */
static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/**
 * Skip whitespace characters
 * @param input: Input string
 * @param i: Current position
 * @return: New position after whitespace
 */
static int	skip_whitespace(char *input, int i)
{
	while (input[i] && is_whitespace(input[i]))
		i++;
	return (i);
}

/**
 * Get the type of a token based on its value
 * @param str: Token string
 * @return: Token type
 */
static int	get_token_type(char *str)
{
	if (!str)
		return (TOKEN_EOF);
	if (ft_strcmp(str, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(str, "<") == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strcmp(str, ">") == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strcmp(str, ">>") == 0)
		return (TOKEN_REDIR_APPEND);
	if (ft_strcmp(str, "<<") == 0)
		return (TOKEN_HEREDOC);
	return (TOKEN_WORD);
}

/**
 * Extract a word token (handles quotes)
 * @param input: Input string
 * @param start: Start position
 * @param end: Pointer to store end position
 * @return: Word string or NULL on error
 */
static char	*extract_word(char *input, int start, int *end)
{
	int		i;
	int		in_single_quote;
	int		in_double_quote;
	char	*word;

	i = start;
	in_single_quote = 0;
	in_double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote)
		{
			if (is_whitespace(input[i]) || is_operator(input[i]))
				break ;
		}
		i++;
	}
	*end = i;
	word = malloc(i - start + 1);
	if (!word)
		return (NULL);
	ft_strncpy(word, input + start, i - start);
	word[i - start] = '\0';
	return (word);
}

/**
 * Extract an operator token
 * @param input: Input string
 * @param start: Start position
 * @param end: Pointer to store end position
 * @return: Operator string or NULL on error
 */
static char	*extract_operator(char *input, int start, int *end)
{
	char	*op;

	if (input[start] == '>' && input[start + 1] == '>')
	{
		*end = start + 2;
		op = ft_strdup(">>");
	}
	else if (input[start] == '<' && input[start + 1] == '<')
	{
		*end = start + 2;
		op = ft_strdup("<<");
	}
	else
	{
		*end = start + 1;
		op = malloc(2);
		if (op)
		{
			op[0] = input[start];
			op[1] = '\0';
		}
	}
	return (op);
}

/**
 * Main tokenization function
 * @param input: Input string to tokenize
 * @return: Head of token list or NULL on error
 */
t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*new_token;
	char	*token_value;
	int		i;
	int		end;

	if (!input)
		return (NULL);
	head = NULL;
	i = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		if (is_operator(input[i]))
		{
			token_value = extract_operator(input, i, &end);
			if (!token_value)
			{
				free_tokens(head);
				return (NULL);
			}
			new_token = create_token(token_value, get_token_type(token_value));
			free(token_value);
		}
		else
		{
			token_value = extract_word(input, i, &end);
			if (!token_value)
			{
				free_tokens(head);
				return (NULL);
			}
			new_token = create_token(token_value, TOKEN_WORD);
			free(token_value);
		}
		if (!new_token)
		{
			free_tokens(head);
			return (NULL);
		}
		add_token(&head, new_token);
		i = end;
	}
	return (head);
}

/**
 * Debug function to print tokens
 * @param tokens: Head of token list
 */
void	print_tokens(t_token *tokens)
{
	t_token		*current;
	const char	*type_names[] = {
		"UNKNOWN", "WORD", "PIPE", "REDIR_IN", 
		"REDIR_OUT", "REDIR_APPEND", "HEREDOC", "EOF"
	};

	current = tokens;
	printf("=== TOKENS ===\n");
	while (current)
	{
		printf("Type: %-12s Value: '%s'\n", 
			type_names[current->type], current->value);
		current = current->next;
	}
	printf("==============\n");
}