#include "minishell.h"
#include <stdlib.h>
#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>

int beginning(t_vars *vars)
{
    int i;
    int count;

    count = double_counter(vars->env);
    i = search_in_env(vars->env, "OLDPWD=", count);
    if (i != -1)
        return (null_free(&vars->env[i]), re_init_env(vars, count, 1), 1);
    return (1);
}

int setting(t_vars *vars, char **env, int situation)
{
    if (!init_env(vars, env))
        return (err_msg("Env not initialized"), 0);
    vars->input = NULL;
    vars->input_parsed = NULL;
    vars->output = NULL;
    vars->user_pwd = NULL;
    vars->file_created = 0;
    vars->file_opened = 0;
    vars->exit_stat = 0;
    vars->hist = 0;
    if (situation)
        return (beginning(vars));
    return (1);
}

int *find_dir(char **env)
{
    char    *pwd;
    char    *ret;
    char    **split;
    int     i;

    pwd = getcwd(NULL, 0);
    if (!pwd)
		return (perror("getcwd"), ft_strdup(".. "));
	i = search_in_env(env, "HOME=", double_counter(env));
	if (i != -1 && ft_strncmp(pwd, env[i] + 5, ft_strlen(env[i])) == 0)
		ret = ft_strdup(" ~");
	else if (ft_strncmp(pwd, "/", 2) == 0)
		ret = ft_strdup(" /");
	else
	{
		split = ft_split(pwd, '/');
		if (!split)
			return (null_free(&pwd), NULL);
		i = double_counter(split);
		ret = ft_strjoin(" ", split[i - 1]);
		free_doubles(split);
	}
	return (null_free(&pwd), ret);
}

int prompter(char **env, t_vars *vrs)
{
    char    **vars;
    int     i;

    vars = malloc(sizeof(char *) * 5);
    if (!vars)
        return (0);
    i = search_in_env(env, "USER=", double_counter(env));
    if (i == -1)
        vars[0] = ft_strdup("user");
    else
        vars[0] = ft_strdup(env[i] + 5);
    vars[1] = ft_strdup("@");
    vars[2] = find_dir(env);
    vars[3] = ft_strdup(" $ ");
    if (!vars[0] || !vars[1] || !vars[2] || !vars[3])
        return (err_msg("Error Strdup"), free_doubles(vars), 1);
    vars[4] = NULL;
    return (append_doubles(&vrs->user_pwd, vars, 0), free_doubles(vars), 1);
}

int main(int argc, char **argv, char **env)
{
    t_vars  vars;

    (void)argv;
    if (argc != 1)
        return (err_msg("Error\nRun Without Arguments"), 1);
    if (!setting)
        exit(EXIT_FAILURE);
    while (1)
    {
        reset_vars(&vars);
        if (!promter(vars.env, &vars) || !vars.user_pwd)
            return (err_msg("Error Prompter"))
    }
}