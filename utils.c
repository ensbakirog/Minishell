#include "minishell.h"
#include <stdlib.h>

int double_counter(char **str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

int reset_vars(t_vars *vars)
{
    reset_fds(vars);
    vars->file_created = 0;
    vars->file_opened = 0;
    null_free(&vars->input);
    null_free(&vars->output);
    free_doubles(vars->input_parsed);
    reser_fds(vars);
    vars->input_parsed = NULL;
    vars->hist = 0;
    return (1);
}
