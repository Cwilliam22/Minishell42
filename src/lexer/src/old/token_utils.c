/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:23:24 by alfavre           #+#    #+#             */
/*   Updated: 2025/04/09 12:57:50 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/lexer.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static void	handle_quotes(char *input, int *i, int *single_quote, int *double_quote)
{
	if (input[*i] == '\'' && !(*double_quote))
	{
		*single_quote = !(*single_quote);
		(*i)++;
	}
	else if (input[*i] == '\"' && !(*single_quote))
	{
		*double_quote = !(*double_quote);
		(*i)++;
	}
	else
		(*i)++;
}

char	*extract_word(char *input, int *i)
{
	int	start;
	int	length;
	char	*word;
	int	single_quote;
	int	double_quote;

	start = *i;
	length = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[*i] && ((single_quote || double_quote)
		|| (!is_whitespace(input[*i]) && !is_special_char(input[*i]))))
	{
		handle_quotes(input, i, &single_quote, &double_quote);
		length = *i - start;
	}
	if (single_quote || double_quote)
		printf("Warning: unclosed quote\n");
	word = malloc(sizeof(char) * (length + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, input + start, length + 1);
	return (word);
}
