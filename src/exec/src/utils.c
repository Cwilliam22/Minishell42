/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:17:09 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/02 18:17:12 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strfchr(const char *s, int c)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	i--;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	skip_n(char **arg)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	if (!arg)
		return (-1);
	while (arg[j])
	{
		if (strncmp("-n", arg[i], 2) == 0)
			i++;
		j++;
	}
	return (i);
}

int	word_with_dollar(char *arg, t_shell *shell)
{
	size_t	j;
	char	*var;
	char	*value;
	int		len;

	j = 0;
	printf("I'm the word_with_dollar function\n");
	while (arg[j])
	{
		if (arg[j] == '$')
		{
			printf("I have the char $\n");
			j++;
			if (arg[j] == '?')
			{
				ft_printf("%d", shell->exec->out);
				j++;
			}
			else if (ft_isalpha(arg[j]))
			{
				var = ft_strdup_from_index(arg, j);
				value = ft_strdup(find_value_in_env(var, shell->exec));
				len = ft_strlen(var);
				ft_printf("%s", value);
				j += len;
				free(var);
				free(value);
			}
			else if (ft_isdigit(arg[j]))
				j++;
		}
		ft_printf("%c", arg[j]);
		j++;
	}
	return (1);
}

int	ft_printf_arg(char **tab_arg, int index, int option, t_shell *shell)
{
	int	i;

	i = index;
	while (tab_arg[i])
	{
		if (ft_search_char(tab_arg[i], '$'))
			word_with_dollar(tab_arg[i], shell);
		else
			ft_printf("%s", tab_arg[i]);
		if (tab_arg[i + 1])
			ft_printf(" ");
		i++;
	}
	if (option == 0)
		ft_printf("\n");
	return (1);
}

int	copy_env2(char ***dest, char ***src, t_exec *exec)
{
	int	i;
	int	j;

	i = exec->nbr_var_env;
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (0);
	i = 0;
	while (src[i])
	{
		j = 0;
		while (src[i][j])
		{
			dest[i][j] = ft_strdup(src[i][j]);
			j++;
		}
		i++;
	}
	dest[i] = NULL;
	return (1);
}

void	change_oldpwd_or_pwd(t_exec *exec, int option)
{
	int	index;

	if (option == 1)
	{
		index = find_sth_in_env("OLDPWD", exec->env);
		if (index == -1)
			new_var(exec->oldpwd, "OLDPWD", exec);
		else
		{
			exec->oldpwd = ft_strdup(getcwd(NULL, 0));
			free(exec->env[index][1]);
			exec->env[index][1] = ft_strdup(exec->oldpwd);
		}
	}
	else if (option == 0)
	{
		index = find_sth_in_env("PWD", exec->env);
		if (index == -1)
			return ;
		exec->pwd = ft_strdup(getcwd(NULL, 0));
		free(exec->env[index][1]);
		exec->env[index][1] = ft_strdup(exec->pwd);
	}
}

int	is_a_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha((int)arg[i]))
		return (0);
	while (arg[i])
	{
		if (!ft_isalpha((int)arg[i]) || !ft_isdigit((int)arg[i])
			|| arg[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int	look_at_identifier(t_shell *shell)
{
	int		i;
	char	**args;

	i = 0;
	args = shell->cmd_list->args;
	while (args[i])
	{
		if (!is_a_valid_identifier(args[i]))
			return (exit_codes(shell, GENERAL_ERROR, ""), 0);
		i++;
	}
	return (exit_codes(shell, SUCCESS, ""), 1);
}

int	exit_codes(t_shell *shell, int out, char *str)
{
	shell->exec->out = out;
	if (str)
		printf("%s", str);
	return (1);
}

int	its_absolute_path(t_shell *shell)
{
	if (shell->cmd_list->args[0][0] == '/')
		shell->exec->cmd_path = ft_strdup(shell->cmd_list->args[0]);
	if (!shell->exec->cmd_path)
		return (0);
	return (1);
}

int	its_relative_path(t_shell *shell)
{
	if (shell->cmd_list->args[0][0] == '.'
		&& shell->cmd_list->args[0][1] == '/')
		shell->exec->cmd_path = ft_strdup(shell->cmd_list->args[0]);
	if (!shell->exec->cmd_path)
		return (0);
	return (1);
}
