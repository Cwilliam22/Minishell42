/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:10:27 by wcapt             #+#    #+#             */
/*   Updated: 2025/03/22 15:35:28 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

char	**split_var_env(char *env_var)
{
	char	*sign;
	char	**split;

	split = malloc(3 * sizeof(char *));
	if (!split)
		return (NULL);
	sign = ft_strchr(env_var, '=');
	if (!sign)
	{
		split[0] = ft_strdup(env_var);
		split[1] = NULL;
	}
	else
	{
		*sign = '\0';
		split[0] = ft_strdup(env_var);
		split[1] = ft_strdup(sign + 1);
		split[2] = NULL;
	}
	return (split);
}

char	***copy_env(char **envp)
{
	int		i;
	int		j;
	char	***env;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	env = malloc((i + 1) * sizeof(char **));
	if (!env)
		return (NULL);
	while (j < i)
	{
		env[j] = split_var_env(envp[j]);
		j++;
	}
	env[i] = NULL;
	return (env);
}

void	print_env(char ***env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("[%s] [%s]\n", env[i][0], env[i][1] ? env[i][1] : "NULL");
		i++;
	}
}

/*
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char ***env;

	env = copy_env(envp);
	if (!env) 
		return (1);
	print_env(env);
	return (0);
}
*/
