/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:49:18 by wcapt             #+#    #+#             */
/*   Updated: 2025/03/18 16:33:55 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include <stdio.h>
#include <unistd.h>
# include "../libft/includes/libft.h"

// copy_env.c
char ***copy_env(char **envp);
char **split_var_env(char *env_var);
void print_env(char ***env);

// path.c
int find_var_path(char ***env);
char *read_in_path(char ***env, int place);
int apply_path(char ***env, char *command);

// utils.c
char *ft_strfchr(const char *s, int c);

#endif