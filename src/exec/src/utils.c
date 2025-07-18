/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:17:09 by wcapt             #+#    #+#             */
/*   Updated: 2025/07/08 16:56:13 by wcapt            ###   ########.fr       */
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

int	exit_codes(t_shell *shell, int out, char *str)
{
	shell->exec->out = out;
	if (str)
		printf("%s", str);
	return (1);
}
