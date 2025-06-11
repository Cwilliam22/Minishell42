#include "minishell.h"


int ft_lstlen(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd)
    {
        i++;
        cmd = cmd->next;
    }
    return (i);    
}

int ft_lstcmdlen(t_cmd *cmd, int index)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (i < index && cmd)
    {
        cmd = cmd->next;
        i++;
    }
    // security
    if (!cmd || !cmd->args) 
        return 0;
    while (cmd->args[count])
        count++;
    return (count);
}

char **ft_lstcmd_copy(t_cmd *cmd, int index, t_exec *exec)
{
    char **command;
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < index && cmd)
    {
        cmd = cmd->next;
        i++;
    }
    if (!cmd || !cmd->args) 
        return 0;
    command = malloc(sizeof(char *) * (ft_lstcmdlen(cmd, index) + 1));
    if (!command)
        return (NULL);
    exec->cmd = ft_strdup(cmd->args[0]);
	 while (cmd->args[j])
	{
		command[j] = ft_strdup(cmd->args[j]);
		j++;
	}
	command[j] = NULL;
    return (command);
}
