#include "minishell.h"

/* Stubs temporaires - fonctions vides pour compiler */
void	init_env_list(t_shell *shell, char **envp)
{
	(void)shell; (void)envp;
	/* TODO: Implement environment initialization */
}

char	**env_list_to_array(t_env *env_list)
{
	(void)env_list;
	/* TODO: Convert env list to array */
	return NULL;
}

void	free_env_list(t_env *env_list) { (void)env_list; }
void	free_env_array(char **env_array) { (void)env_array; }
