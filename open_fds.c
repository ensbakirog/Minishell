#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int reset_fds(t_vars *vars)
{
    if (vars->file_created)
        if (dup2(vars->origin_stdout, STDOUT_FILENO) == -1)
            return (perror("dup2"), 0);
    if (vars->file_opened)
        if (dup2(vars->origin_stdin, STDIN_FILENO))
            return (perror("dup2"), 0);
    return (1);
}