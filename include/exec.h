/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:49:18 by wcapt             #+#    #+#             */
/*   Updated: 2025/06/09 15:17:39 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include <stdio.h>
#include <unistd.h>

// To use the function waitpid()
#include <sys/wait.h>

#include "../src/exec/libft/includes/libft.h"

#include "lexer.h"

typedef struct s_exec
{
	char			**args;
	char			***env;
	char			*cmd_path;
	char			*path;
	int				nbr_process;
	int				nbr_pipes;
	int				nbr_var_env;
	int				nbr_arg;
	int				fd_in;
	int				fd_out;
	int				out;
	char			*cmd;
	int				is_pipe;
}	t_exec;

typedef struct s_builtin
{
	char	*builtin;
	int		(*fonction)(char **args, t_exec *exec);
}	t_builtin;

// exec.c
int		ft_exec(char ***tab_arg, t_exec *exec);

// copy_env.c
int		copy_env1(char **envp, t_exec *exec);
char	**split_var_env(char *env_var);
int		print_env(char ***env);
int		print_env_sorted(t_exec *exec);
char	**copy_env_sorted(t_exec *exec);

// path.c
int		find_var_path(char ***env);
char	*read_in_path(char ***env, int place);
int		apply_path(t_exec *exec);

// Identification.c
int		identification(t_command *cmd, t_exec *exec);
int		its_a_builtin(char **arg, t_exec *exec);
int		execute_externe(char **args, t_exec *exec);
char	**set_my_fucking_error(t_exec *exec);

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
int		ft_tablen_3d(char ***tab_arg);
int		ft_tablen_2d(char **tab_arg);

// free.c
int		free_env(char ***env);
int		free_array(char **array);
int		free_var(t_exec *exec);
int		free_all_env(t_exec *exec);
int		free_pipes(int **pipes, t_exec *exec);

// get.c
int		find_sth_in_env(char *variable, char ***env);
char	*find_value_in_env(char *variable, t_exec *exec);
int		find_var_place(char *new_variable, t_exec *exec);
int		get_var_in_order(int index, t_exec *exec);

// new_var.c
int		new_var(char *new_value, char *new_variable, t_exec *exec);
int		replace_value_var(char *new_value, int i, char ***env);

// unset.c
int		unset_var(int index, t_exec *exec);

// pipe.c
int		pipeline(t_command *cmd, t_exec *exec);
int		execute_pipeline(t_command *cmd, t_exec *exec, int **pipes);
int		close_pipes(int **pipes, t_exec *exec);

// list.c
int		ft_lstlen(t_command *cmd);
char	**ft_lstcmd_copy(t_command *cmd, int index, t_exec *exec);


#endif