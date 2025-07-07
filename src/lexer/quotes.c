/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:37:05 by root              #+#    #+#             */
/*   Updated: 2025/07/07 10:00:07 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Get environment variable value
 * @param key: Variable name
 * @param shell: Shell structure
 * @return: Variable value or empty string if not found
 */
char	*get_env_var(char *key, t_shell *shell)
{
	t_exec	*current;
	int		env_index;

	if (!key || !shell)
		return (ft_strdup(""));
	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(shell->exit_status));
	current = shell->exec;
	env_index = find_sth_in_env(key, current->env);
	if (env_index >= 0)
		return (find_value_in_env(key, current));
	else
		return (ft_strdup(""));
}

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

/**
 * Expand variables in string (handle $ expansions)
 * @param str: String to expand
 * @param shell: Shell structure
 * @return: Expanded string or NULL on error
 */
char	*expand_variables(char *str, t_shell *shell)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	int		i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			var_name = extract_var_name(str + i + 1, &i);
			if (var_name && var_name[0] != '\0')
			{
				var_value = get_env_var(var_name, shell);
				result = join_and_free(result, var_value);
			}
			else
			{
				result = append_char_to_str(result, '$');
				i++;
			}
			free(var_name);
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
