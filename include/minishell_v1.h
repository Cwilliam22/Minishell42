/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_v1.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:35:19 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 13:53:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                 INCLUDES                                   */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/* ************************************************************************** */
/*                                 DEFINES                                    */
/* ************************************************************************** */

# define PROMPT "minishell$ "
# define MAX_PATH 4096
# define MAX_ARGS 1024

/* Exit codes */
# define SUCCESS 0
# define GENERAL_ERROR 1
# define MISUSE_BUILTIN 2
# define COMMAND_NOT_FOUND 127
# define COMMAND_NOT_EXECUTABLE 126

/* Token types */
# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIR_IN 3
# define TOKEN_REDIR_OUT 4
# define TOKEN_REDIR_APPEND 5
# define TOKEN_HEREDOC 6
# define TOKEN_EOF 7

/* File descriptor constants */
# define STDIN 0
# define STDOUT 1
# define STDERR 2

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */

/* Token structure for lexical analysis */
typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

/* Redirection structure */
typedef struct s_redir
{
	int				type;
	char			*file;
	int				fd;
	struct s_redir	*next;
}	t_redir;

/* Command structure */
typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	int				pipe_fd[2];
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

/* Environment variable structure */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* Main shell structure */
typedef struct s_shell
{
	t_env			*env_list;
	char			**env_array;
	t_cmd			*cmd_list;
	t_token			*token_list;
	int				exit_status;
	int				in_heredoc;
	char			*input_line;
}	t_shell;

/* ************************************************************************** */
/*                            GLOBAL VARIABLE                                 */
/* ************************************************************************** */

/* Global variable for signal handling (only signal number allowed) */
extern int	g_signal_received;

/* ************************************************************************** */
/*                            FUNCTION PROTOTYPES                             */
/* ************************************************************************** */

/* ============================= MAIN ===================================== */
int		main(int argc, char **argv, char **envp);

/* ============================= SIGNALS ================================== */
void	setup_signals(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	setup_heredoc_signals(void);
void	setup_exec_signals(void);

/* ============================= LEXER ===================================== */
t_token	*tokenize(char *input);
t_token	*create_token(char *value, int type);
void	add_token(t_token **head, t_token *new_token);
void	free_tokens(t_token *tokens);

/* ============================= PARSER ==================================== */
t_cmd	*parse_tokens(t_token *tokens, t_shell *shell);
t_cmd	*create_command(void);
void	add_command(t_cmd **head, t_cmd *new_cmd);
void	free_commands(t_cmd *commands);

/* ============================= QUOTES ==================================== */
char	*handle_quotes(char *str, t_shell *shell);
char	*expand_variables(char *str, t_shell *shell);
char	*get_env_value(char *key, t_shell *shell);
int		count_quotes(char *str, char quote_type);
char	*remove_quotes(char *str);

/* ============================= EXECUTOR ================================== */
int		execute_pipeline(t_shell *shell);
int		execute_command(t_cmd *cmd, t_shell *shell);
int		execute_builtin(t_cmd *cmd, t_shell *shell);
int		execute_external(t_cmd *cmd, t_shell *shell);
char	*find_executable(char *cmd, t_shell *shell);

/* ============================= PIPES ===================================== */
int		setup_pipes(t_cmd *commands);
int		setup_pipe_fds(t_cmd *cmd, t_cmd *next_cmd);
void	close_pipe_fds(t_cmd *commands);
int		wait_for_children(t_cmd *commands);

/* ============================= REDIRECTIONS ============================= */
int		setup_redirections(t_cmd *cmd);
int		handle_input_redir(t_redir *redir);
int		handle_output_redir(t_redir *redir);
int		handle_append_redir(t_redir *redir);
int		handle_heredoc(t_redir *redir, t_shell *shell);
t_redir	*create_redirection(int type, char *file);
void	add_redirection(t_redir **head, t_redir *new_redir);
void	free_redirections(t_redir *redirections);

/* ============================= BUILTINS ================================== */
int		is_builtin(char *cmd);
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_shell *shell);
int		builtin_pwd(void);
int		builtin_export(char **args, t_shell *shell);
int		builtin_unset(char **args, t_shell *shell);
int		builtin_env(t_shell *shell);
int		builtin_exit(char **args, t_shell *shell);

/* ============================= ENVIRONMENT ============================== */
t_env	*create_env_node(char *key, char *value);
void	add_env_node(t_env **head, t_env *new_node);
void	remove_env_node(t_env **head, char *key);
t_env	*find_env_node(t_env *env_list, char *key);
char	**env_list_to_array(t_env *env_list);
void	free_env_list(t_env *env_list);
void	free_env_array(char **env_array);
void	init_env_list(t_shell *shell, char **envp);
void	update_env_value(t_shell *shell, char *key, char *value);

/* ============================= PATH UTILS =============================== */
char	**get_paths(t_shell *shell);
char	*join_path(char *dir, char *cmd);
int		is_executable(char *path);
int		file_exists(char *path);
char	*get_current_dir(void);

/* ============================= STRING UTILS ============================= */
char	**split_args(char *str);
void	free_args(char **args);
char	*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2);
char	*ft_strndup(const char *s, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

/* ============================= ERROR HANDLING ============================ */
void	print_error(char *cmd, char *arg, char *msg);
void	print_syntax_error(char *token);
void	print_export_error(char *arg);
void	perror_exit(char *msg);
int		check_syntax(t_token *tokens);

/* ============================= MEMORY MANAGEMENT ========================= */
void	free_shell(t_shell *shell);
void	*safe_malloc(size_t size);
char	*safe_strdup(const char *s);

/* ============================= UTILS ===================================== */
int		ft_isalnum_underscore(int c);
int		is_valid_identifier(char *str);
void	print_sorted_env(t_env *env_list);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);

/* ============================= MISSING FUNCTIONS ======================== */

/* Redirection utilities */
t_redir	*create_redirection(int type, char *file);
void	add_redirection(t_redir **head, t_redir *new_redir);
void	free_redirections(t_redir *redirections);

/* Quote utilities */
int		check_quotes(char *str);
int		count_quotes(char *str, char quote_type);
char	*remove_quotes(char *str);

/* Error utilities */
void	print_syntax_error(char *token);
void	print_error(char *cmd, char *arg, char *msg);

/* Debug functions */
void	print_tokens(t_token *tokens);
void	print_commands(t_cmd *commands);

#endif