/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_interface.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:38:13 by alfavre           #+#    #+#             */
/*   Updated: 2025/05/08 13:02:44 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Fonction pour convertir t_env en char ***env (format requis par ft_exec)
*/
static char	***convert_env_format(t_env *env)
{
	char	***env_array;
	t_env	*current;
	int		count;
	int		i;

	// Compter le nombre de variables d'environnement
	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	
	// Allouer le tableau principal (taille count + 1 pour le NULL final)
	env_array = malloc(sizeof(char **) * (count + 1));
	if (!env_array)
		return (NULL);
	
	// Remplir le tableau
	i = 0;
	current = env;
	while (current && i < count)
	{
		// Chaque entrée est un tableau de 2 chaînes: clé et valeur
		env_array[i] = malloc(sizeof(char *) * 3);
		if (!env_array[i])
		{
			// Gérer l'erreur ici (libérer la mémoire déjà allouée)
			while (--i >= 0)
			{
				free(env_array[i][0]);
				free(env_array[i][1]);
				free(env_array[i]);
			}
			free(env_array);
			return (NULL);
		}
		env_array[i][0] = strdup(current->key);
		env_array[i][1] = strdup(current->value);
		env_array[i][2] = NULL;
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

/*
** Fonction pour libérer la mémoire du tableau env
*/
static void	free_env_array(char ***env_array)
{
	int	i;
	int	j;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		j = 0;
		while (env_array[i][j])
		{
			free(env_array[i][j]);
			j++;
		}
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

/*
** Fonction d'interface pour exécuter une liste de commandes
** avec votre fonction ft_exec
*/
int	execute_commands(t_command *cmd_list, t_env *env)
{
	t_command	*current;
	t_exec	exec;
	int		status;
	char	***env_array;

	if (!cmd_list || !env)
		return (1);
	// Convertir l'environnement au format attendu par ft_exec
	env_array = convert_env_format(env);
	if (!env_array)
		return (1);
	status = 0;
	current = cmd_list;
	while (current)
	{
		// Configuration de l'exécution
		memset(&exec, 0, sizeof(t_exec));
		exec.env = env_array;
		// Exécution de la commande
		if (current->args && current->args[0])
		{
			status = ft_exec(current->args, &exec);
			// Gestion des redirections ici si nécessaire
			// ...
			
			// Gestion des pipes ici si nécessaire
			// ...
		}
		current = current->next;
	}
	// Libération de la mémoire
	free_env_array(env_array);
	return (status);
}
