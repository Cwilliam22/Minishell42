/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:49:18 by wcapt             #+#    #+#             */
/*   Updated: 2025/03/22 17:13:52 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

typedef struct s_exec
{
	char			**args;
	char			*cmd_path;
	int				fd_in;
	int				fd_out;
	int				is_pipe;
	struct s_exec	*next;
}	t_exec;

typedef struct s_builtin
{
	char	*builtin;
	int		(*fonction)(char **args, char ***env);
}	t_builtin;

// copy_env.c
char	***copy_env(char **envp);
char	**split_var_env(char *env_var);
void	print_env(char ***env);

// path.c
int		find_var_path(char ***env);
char	*read_in_path(char ***env, int place);
int		apply_path(char ***env, char *command);

// builtin1.;
int builtin_echo();
int builtin_cd();
int builtin_pwd();
int builtin_export();

// builtin2.c
int builtin_unset();
int builtin_env();
int builtin_exit();

// utils.c
char	*ft_strfchr(const char *s, int c);

#endif