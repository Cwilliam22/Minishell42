/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:21:03 by alfavre           #+#    #+#             */
/*   Updated: 2025/07/06 14:21:07 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Process unquoted character for handle_quotes function
 * @param result: Current result string
 * @param str: Original string
 * @param index: Pointer to current index
 * @param shell: Shell structure
 * @return: Updated result string
 */
char	*process_unquoted_char(char *result, char *str,
	int *index, t_shell *shell)
{
	char	*section;
	char	*processed;
	int		start;

	start = *index;
	while (str[*index] && str[*index] != '\'' && str[*index] != '"')
		(*index)++;
	if (*index > start)
	{
		section = ft_substr(str, start, *index - start);
		processed = expand_variables(section, shell);
		result = join_and_free(result, processed);
		free(section);
	}
	return (result);
}

/**
 * Extract unquoted section from string
 * @param str: String to extract from
 * @param index: Pointer to current index (updated)
 * @return: Extracted section or NULL on error
 */
char	*extract_unquoted_section(char *str, int *index)
{
	char	*section;
	int		start;

	if (!str || !index)
		return (NULL);
	start = *index;
	while (str[*index] && str[*index] != '\'' && str[*index] != '"')
		(*index)++;
	if (*index > start)
	{
		section = ft_substr(str, start, *index - start);
		return (section);
	}
	return (ft_strdup(""));
}

/**
 * Process quoted section for handle_quotes function
 * @param result: Current result string
 * @param str: Original string
 * @param index: Pointer to current index
 * @param shell: Shell structure
 * @return: Updated result string
 */
char	*process_quoted_section(char *result, char *str,
	int *index, t_shell *shell)
{
	char	*section;
	char	*processed;
	int		quote_end;

	quote_end = find_matching_quote(str, *index);
	if (quote_end == -1)
		return (free(result), NULL);
	section = ft_substr(str, *index + 1, quote_end - *index - 1);
	if (str[*index] == '"')
		processed = expand_variables(section, shell);
	else if (str[*index] == '\'')
		processed = ft_strdup(section);
	else
		return (free(section), free(result), NULL);
	result = join_and_free(result, processed);
	free(section);
	*index = quote_end + 1;
	return (result);
}
