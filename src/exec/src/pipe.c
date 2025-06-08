#include "../../../include/exec.h"

int pipeline(t_command *cmd, t_exec *exec)
{
    int **pipes;
    int i;

    i = 0;
    pipes = malloc(sizeof(int *) * exec->nbr_pipes);
    while (i < exec->nbr_pipes)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        pipe(pipes[i]);
        i++;
    }
    if (!execute_pipeline(cmd, exec, pipes))
        return (ft_printf("Error in execute pipeline\n"), 0);
    return (1);
}

int execute_pipeline(t_command *cmd, t_exec *exec, int **pipes)
{
    pid_t   *pids;
    int    i;
    int     status;
    
    i = 0;
    pids = malloc(sizeof(pid_t) * exec->nbr_process);
    if (!pids)
        return (ft_printf("Error malloc pids\n"), 0);
    while (i < exec->nbr_process)
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
            if (i == 0)
            {
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            else if (i > 0 && i < exec->nbr_process - 1)
            {
                dup2(pipes[i][1], STDOUT_FILENO);
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }
            else if (i == exec->nbr_process - 1)
                dup2(pipes[i - 1][0], STDIN_FILENO);
            if (!close_pipes(pipes, exec))
            {
                ft_printf("Error in close pipes\n");
                exit(1);
            }
            if (!identification(cmd, exec, i))
		        return (1);
            exit(0);
        }
        i++;
    }
    if (!close_pipes(pipes, exec))
        return (ft_printf("Error in close pipes\n"), 0);
    i = 0;
    while (i < exec->nbr_process)
    {
        if (pids[i] > 0)
            waitpid(pids[i], &status, 0);
        else if (pids[i] < 0)
            return (ft_printf("Error in fork\n"), 0);
        i++;
    }
    // free pids 
    // free pipes
    return (1);
}

int close_pipes(int **pipes, t_exec *exec)
{
    int j;

    j = 0;
    while (j < exec->nbr_process - 1) 
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
        j++;
    }
    return (1);
}
// free pids tab
// exit(0) au cas ou il ne trouve pas la commande,
    // qu'il continue a executer le code dans le child 
// i == 0 (pas de stdin)
// i == nb_process - 1 (pas de stdout)

