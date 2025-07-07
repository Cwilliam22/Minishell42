/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:37:05 by root              #+#    #+#             */
/*   Updated: 2025/07/07 11:42:06 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Extract variable name from string and update index
 * @param str: String starting at variable name
 * @param index: Pointer to current index (updated)
 * @return: Variable name or NULL on error
 */
char	*extract_var_name(char *str, int *index)
{
	char	*var_name;
	int		len;

	if (!str || !index)
		return (NULL);
	if (str[0] == '?')
		return (*index += 2, ft_strdup("?"));
	if (ft_isdigit(str[0]))
	{
		*index += 2;
		var_name = ft_substr(str, 0, 1);
		return (var_name);
	}
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (ft_strdup(""));
	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	*index += len + 1;
	var_name = ft_substr(str, 0, len);
	return (var_name);
}


static char	*process_variable(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	char	*result;

	var_name = extract_var_name(str + *i + 1, i);
	if (var_name && var_name[0] != '\0')
	{
		var_value = get_env_var(var_name, shell);
		if (var_value)
			result = ft_strdup(var_value);
		else
			result = ft_strdup("");
	}
	else
	{
		result = ft_strdup("$");
		(*i)++;
	}
	free(var_name);
	return (result);
}

/**
 * Expand variables in a string
 * @param str: Input string
 * @param shell: Shell structure
 * @return: New string with variables expanded
 */
char	*expand_variables(char *str, t_shell *shell)
{
	char	*result;
	char	*temp;
	int		i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			temp = process_variable(str, &i, shell);
			result = join_and_free(result, temp);
		}
		else
			result = append_char_to_str(result, str[i++]);
	}
	return (result);
}

/**
 * Process quoted sections and handle variable expansion
 * @param str: Input string
 * @param shell: Shell structure
 * @return: Processed string without quotes
 */
char	*handle_quotes(char *str, t_shell *shell)
{
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			result = process_quoted_section(result, str, &i, shell);
		else
			result = process_unquoted_char(result, str, &i, shell);
	}
	return (result);
}

/**
 * Check if quotes are properly balanced
 * @param str: String to check
 * @return: 1 if balanced, 0 otherwise
 */
int	check_quotes(char *str)
{
	int		i;
	int		in_quote;
	char	quote_type;

	if (!str)
		return (1);
	i = 0;
	in_quote = 0;
	while (str[i])
	{
		if (!in_quote && (str[i] == '\'' || str[i] == '"'))
		{
			quote_type = str[i];
			in_quote = 1;
		}
		else if (in_quote && str[i] == quote_type)
			in_quote = 0;
		i++;
	}
	return (!in_quote);
}
