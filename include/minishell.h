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

# define PROMPT "\033[32mminishell$> \033[0m"
# define MAX_PATH 4096
# define MAX_ARGS 1024

/* Exit codes */
# define SUCCESS 0
# define GENERAL_ERROR 1
# define MISUSE_BUILTIN 2
# define COMMAND_NOT_FOUND 127
# define COMMAND_NOT_EXECUTABLE 126
# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131

/* Token types */
# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIR_IN 3
# define TOKEN_REDIR_OUT 4
# define TOKEN_REDIR_APPEND 5
# define TOKEN_HEREDOC 6
# define TOKEN_EOF 7
# define TOKEN_VAR 8

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

/* Assignment structure for export commands */
typedef struct s_assignment
{
	char					*key;
	char					*value;
	struct s_assignment		*next;
}	t_assignment;

/* Command structure */
typedef struct s_cmd
{
	char			**args;
	t_assignment	*assignments;
	t_redir			*redirections;
	int				pipe_fd[2];
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec
{
	char			***env;
	char			*cmd_path;
	char			*path;
	int				nbr_process;
	int				nbr_pipes;
	int				nbr_var_env;
	int				nbr_arg;
	int				out;
	char			*cmd;
	char			*oldpwd;
	char			*pwd;
	int				is_pipe;
	int				rel_path;
	int				abs_path;
	int				shlvl;
	int				exit;
}	t_exec;

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
	t_exec			*exec;
	t_cmd			*cmd_list;
	t_token			*token_list;
	int				exit_status;
	int				in_heredoc;
	char			*input_line;
}	t_shell;

typedef struct s_builtin
{
	char	*builtin;
	int		(*fonction)(t_shell *shell);
}	t_builtin;

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
/* Fonctions de configuration */
void	setup_signals(void);
void	setup_interactive_signals(void);
void	setup_execution_signals(void);
void	setup_heredoc_signals(void);
void	restore_default_signals(void);

/* Fonctions de vérification */
int		check_and_handle_signal(void);
int		signal_received(void);
void	reset_signal(void);
int		get_signal_number(void);

/* Fonctions utilitaires pour processus enfants */
int		wait_child_with_signals(pid_t pid);

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

/* ============================= EXPAND ==================================== */
int		needs_expansion(char *str);
void	expand_commands(t_cmd *commands, t_shell *shell);
void	expand_command_args(t_cmd *cmd, t_shell *shell);

/* ============================= EXECUTOR ================================== */
int		ft_exec(t_shell *shell);
void	init_all(t_exec *exec);
int		identification(t_shell *shell);
int		its_a_builtin(t_shell *shell);
int		execute_externe(char **args, t_shell *shell);
char	**set_my_fucking_error(t_exec *exec);

/* ============================= PATH ================================== */
int		find_var_path(char ***env);
char	*read_in_path(char ***env, int place);
int		apply_path(t_shell *shell);

/* ============================= PIPES ===================================== */
int		pipeline(t_shell *shell);
int		execute_pipeline(t_shell *shell, int **pipes);
int		close_pipes(int **pipes, t_exec *exec);

/* ============================= REDIRECTIONS ============================= */
int		apply_redirections(t_redir *redirs);
int		create_heredoc_pipe(const char *delimiter);

/* Redirection utilities */
t_redir	*create_redirection(int type, char *file);
void	add_redirection(t_redir **head, t_redir *new_redir);
void	free_redirections(t_redir *redirections);

/* ============================= BUILTINS ================================== */
// builtin1.;
int		builtin_echo(t_shell *shell);
int		builtin_cd(t_shell *shell);
int		builtin_pwd(t_shell *shell);
int		builtin_export(t_shell *shell);

// builtin2.c
int		builtin_unset(t_shell *shell);
int		builtin_env(t_shell *shell);
int		builtin_exit(t_shell *shell);

/* ============================= ENVIRONMENT ============================== */
char	**env_list_to_array(t_env *env_list);
void	free_env_list(t_env *env_list);
void	free_env_array(char **env_array);
void	init_env_list(t_shell *shell, char **envp);
int		copy_env1(char **envp, t_exec *exec);
char	**split_var_env(char *env_var);
int		print_env(char ***env);
int		print_env_sorted(t_exec *exec);
char	**copy_env_sorted(t_exec *exec);

// new_var.c
int		new_var(char *new_value, char *new_variable, t_exec *exec);
int		replace_value_var(char *new_value, int i, char ***env);

// unset.c
int		unset_var(int index, t_exec *exec);

/* ============================= ERROR HANDLING ============================ */
void	print_error(char *cmd, char *arg, char *msg);
void	print_syntax_error(char *token);
void	print_export_error(char *arg);
void	perror_exit(char *msg);
int		check_token_syntax(t_token *tokens);
int		is_all_spaces(const char *s);

/* ============================= MEMORY MANAGEMENT ========================= */
void	free_shell(t_shell *shell);
void	*safe_malloc(size_t size);
char	*safe_strdup(const char *s);

// free.c
int		free_env(char ***env);
int		free_array(char **array);
int		free_var(t_exec *exec);
int		free_all_env(t_exec *exec);
int		free_pipes(int **pipes, t_exec *exec);

/* ============================= UTILS ===================================== */
int		ft_isalnum_underscore(int c);
int		is_valid_identifier(char *str);
void	print_sorted_env(t_env *env_list);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);

// utils.c
char	*ft_strfchr(const char *s, int c);
int		word_with_dollar(char *tab_arg, t_shell *shell);
int		ft_printf_arg(char **tab_arg, int index, int option, t_shell *shell);
int		copy_env2(char ***dest, char ***src, t_exec *exec);
void	change_oldpwd_or_pwd(t_exec *exec, int option);
int		exit_codes(t_shell *shell, int out, char *str);
int		look_at_identifier(t_shell *shell);
int		is_a_valid_identifier(char *arg);
int		skip_n(char **arg);
int		its_absolute_path(t_shell *shell);
int		its_relative_path(t_shell *shell);

// len.c
int		ft_envlen(char ***env);
int		ft_tablen_3d(char ***tab_arg);
int		ft_tablen_2d(char **tab_arg);

// get.c
int		find_sth_in_env(char *variable, char ***env);
char	*find_value_in_env(char *variable, t_exec *exec);
int		find_var_place(char *new_variable, t_exec *exec);
int		get_var_in_order(int index, t_exec *exec);

// list.c
int		ft_lstlen(t_cmd *cmd);
char	**ft_lstcmd_copy(t_cmd *cmd, int index, t_exec *exec);

/* ============================= MISSING FUNCTIONS ======================== */

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

/* Assignement */
t_assignment	*create_assignment(char *key, char *value);
void			add_assignment(t_assignment **head, t_assignment *new_assign);
void			free_assignments(t_assignment *assignments);
int				is_assignment_word(char *str);
int				split_assignment(char *assignment, char **key, char **value);

#endif