/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:49:18 by wcapt             #+#    #+#             */
/*   Updated: 2025/04/17 19:47:04 by wcapt            ###   ########.fr       */
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
	char			***env;
	char			***env_sorted;
	char			*cmd;
	char			*cmd_path;
	char			*path;
	int				nbr_arg;
	int				nbr_var_env;
	int				fd_in;
	int				fd_out;
	int				is_pipe;
	struct s_exec	*next;
}	t_exec;

typedef struct s_builtin
{
	char	*builtin;
	int		(*fonction)(char **args, t_exec *exec);
}	t_builtin;

// copy_env.c
int		copy_env1(char **envp, t_exec *exec);
char	**split_var_env(char *env_var);
int		print_env(char ***env);
int		copy_env_sorted(t_exec *exec);

// path.c
int		find_var_path(char ***env);
char	*read_in_path(char ***env, int place);
int		apply_path(char ***env, char *command);

// Identification.c
int		identification(char **arg, t_exec *exec);
int		its_a_builtin(char **arg, t_exec *exec);
int		execute_externe(char **arg, char ***env);

// builtin1.;
int		builtin_echo(char **arg, t_exec *exec);
int		builtin_cd(char **arg, t_exec *exec);
int		builtin_pwd(char **arg, t_exec *exec);
int		builtin_export(char **arg, t_exec *exec);

// builtin2.c
int		builtin_unset(char **arg, t_exec *exec);
int		builtin_env(char **arg, t_exec *exec);
int		builtin_exit(char **arg, t_exec *exec);

// utils.c
char	*ft_strfchr(const char *s, int c);
int		ft_printf_arg(char **tab_arg, int index, int option);
int		copy_env2(char ***dest, char ***src, t_exec *exec);

// len.c
int		ft_envlen(char ***env);
int		ft_tablen(char **tab_arg);

// free.c
int		free_env(char ***env);
int		free_array(char **array);
int		free_all(t_exec *exec);

// get.c
int		find_sth_in_env(char *variable, char ***env);
char	*find_value_in_env(char *variable, t_exec *exec);
int		find_var_place(char *new_variable, t_exec *exec);
int		get_var_in_order(int index, t_exec *exec);

// manage_env.c
int		new_var(char *new_value, char *new_variable, t_exec *exec);
int		new_var_env(char *new_value, char *new_variable, t_exec *exec);
int		new_var_env_sorted(char *new_value, char *new_variable, t_exec *exec);
int		replace_value_var(char *new_value, int i, char ***env);

#endif