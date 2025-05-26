#include "../../../include/exec.h"

int pipeline(char ***tab_arg, t_exec *exec)
{
    int pipes[exec->nbr_process - 1][exec->nbr_process - 1];
    
    pipe(pipes[0]);
    pipe(pipes[1]);
}

