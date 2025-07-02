/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:37:05 by root              #+#    #+#             */
/*   Updated: 2025/07/02 22:18:49 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Get environment variable value
 * @param key: Variable name
 * @param shell: Shell structure
 * @return: Variable value or NULL if not found
 */
char	*get_env_value(char *key, t_shell *shell)
{
	t_exec	*current;
	
	if (!key || !shell)
		return (ft_strdup(""));
	
	/* Handle special variable $? */
	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(shell->exit_status));
	
	current = shell->exec;
	if (find_sth_in_env(key, current->env) >= 0)
		return (find_value_in_env(key, current));
	else
		return (ft_strdup(""));
}

/**
 * Extract variable name from string starting with $
 * @param str: String starting after $
 * @param len: Pointer to store variable name length
 * @return: Variable name or NULL on error
 */
static char	*extract_var_name(char *str, int *len)
{
	int		i;
	char	*var_name;

	if (!str || !len)
		return (NULL);
	
	*len = 0;
	
	/* Handle special case $? */
	if (str[0] == '?')
	{
		*len = 1;
		return (ft_strdup("?"));
	}
	
	/* Variable name must start with letter or underscore */
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (ft_strdup(""));
	
	/* Count valid characters */
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	
	*len = i;
	if (i == 0)
		return (ft_strdup(""));
	
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

/**
 * Append character to string (helper function)
 * @param str: Original string
 * @param c: Character to append
 * @return: New string with character appended
 */
static char	*append_char(char *str, char c)
{
	char	*result;
	char	temp[2];

	if (!str)
		return (NULL);
	
	temp[0] = c;
	temp[1] = '\0';
	result = ft_strjoin(str, temp);
	return (result);
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
	char	*temp;
	int		i;
	int		var_len;

	if (!str)
		return (NULL);
	
	result = ft_strdup("");
	if (!result)
		return (NULL);
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			var_name = extract_var_name(str + i + 1, &var_len);
			if (!var_name)
			{
				free(result);
				return (NULL);
			}
			
			if (var_len > 0)
			{
				var_value = get_env_value(var_name, shell);
				if (var_value)
				{
					temp = ft_strjoin(result, var_value);
					free(result);
					free(var_value);
					if (!temp)
					{
						free(var_name);
						return (NULL);
					}
					result = temp;
				}
				i += var_len + 1;
			}
			else
			{
				/* Invalid variable name, keep the $ */
				temp = append_char(result, '$');
				free(result);
				if (!temp)
				{
					free(var_name);
					return (NULL);
				}
				result = temp;
				i++;
			}
			free(var_name);
		}
		else
		{
			temp = append_char(result, str[i]);
			free(result);
			if (!temp)
				return (NULL);
			result = temp;
			i++;
		}
	}
	
	return (result);
}

/**
 * Find the end of a quoted section
 * @param str: String to search
 * @param start: Start position (after opening quote)
 * @param quote_char: Quote character (' or ")
 * @return: Position of closing quote or -1 if not found
 */
static int	find_quote_end(char *str, int start, char quote_char)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (str[i] == quote_char)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * Process content between quotes
 * @param content: Content between quotes
 * @param quote_type: Type of quote (' or ")
 * @param shell: Shell structure
 * @return: Processed string
 */
static char	*process_quoted_content(char *content, char quote_type, t_shell *shell)
{
	if (quote_type == '\'')
		return (ft_strdup(content));
	else
		return (expand_variables(content, shell));
}

/**
 * Handle quotes and variable expansion in a string
 * @param str: Input string with potential quotes
 * @param shell: Shell structure (can be NULL for basic quote removal)
 * @return: Processed string or NULL on error
 */
char	*handle_quotes(char *str, t_shell *shell)
{
	char	*result;
	char	*section;
	char	*processed;
	char	*temp;
	int		i;
	int		start;
	int		end;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			/* Handle quoted section */
			start = i + 1;
			end = find_quote_end(str, start, str[i]);
			if (end == -1)
			{
				/* Unclosed quote - should have been caught in syntax check */
				free(result);
				return (NULL);
			}
			
			section = ft_substr(str, start, end - start);
			if (!section)
			{
				free(result);
				return (NULL);
			}
			
			processed = process_quoted_content(section, str[i], shell);
			free(section);
			if (!processed)
			{
				free(result);
				return (NULL);
			}
			
			temp = ft_strjoin(result, processed);
			free(result);
			free(processed);
			if (!temp)
				return (NULL);
			result = temp;
			
			i = end + 1;
		}
		else
		{
			/* Handle unquoted section */
			start = i;
			while (str[i] && str[i] != '\'' && str[i] != '"')
				i++;
			
			if (i > start)
			{
				section = ft_substr(str, start, i - start);
				if (!section)
				{
					free(result);
					return (NULL);
				}
				
				processed = expand_variables(section, shell);
				free(section);
				if (!processed)
				{
					free(result);
					return (NULL);
				}
				
				temp = ft_strjoin(result, processed);
				free(result);
				free(processed);
				if (!temp)
					return (NULL);
				result = temp;
			}
		}
	}
	return (result);
}

/**
 * Check if quotes are properly closed
 * @param str: String to check
 * @return: 1 if quotes are balanced, 0 otherwise
 */
int	check_quotes(char *str)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	if (!str)
		return (1);
	
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	
	return (!in_single_quote && !in_double_quote);
}

/**
 * Count the number of specific quote type in string
 * @param str: String to analyze
 * @param quote_type: Quote character to count (' or ")
 * @return: Number of quotes found
 */
int	count_quotes(char *str, char quote_type)
{
	int	i;
	int	count;
	int	in_other_quote;

	if (!str)
		return (0);
	
	i = 0;
	count = 0;
	in_other_quote = 0;
	
	while (str[i])
	{
		if (quote_type == '\'' && str[i] == '"')
			in_other_quote = !in_other_quote;
		else if (quote_type == '"' && str[i] == '\'')
			in_other_quote = !in_other_quote;
		else if (str[i] == quote_type && !in_other_quote)
			count++;
		i++;
	}
	
	return (count);
}

/**
 * Simple quote removal (for basic cases without variable expansion)
 * @param str: String with quotes
 * @return: String without quotes or NULL on error
 */
char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;

	if (!str)
		return (NULL);
	
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	
	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			/* Skip the quote character */
		}
		else if (str[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			/* Skip the quote character */
		}
		else
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	
	result[j] = '\0';
	return (result);
}