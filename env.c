#include "minishell.h"
#include "libft/libft.h"

int	init_env(t_vars *vars, char **env)
{
    int i;

    i = double_counter(env);
    vars->env = ft_calloc(sizeof(char *), (i + 1));
    if (!vars->env)
        return (err_msg("env not set"), 0);
    i = -1;
    while (env[++i])
    {
        vars->env[i] = ft_strdup(env[i]);
        if (!vars->env[i])
            return (free_doubles(vars->env), err_msg("env not set"), 0);
    }
    vars->env[i] = NULL;
    return (1);
}

int	search_in_env(char **env, char *src, int count)
{
	int     i;
	char    **tmp;

	i = -1;
	while (count >= ++i)
	{
		if (!env[i])
			continue;
		tmp = ft_split(env[i], '=');
		if (!tmp)
			return (err_msg("Error split"), -1);
		if (ft_strncmp(tmp[0], src, ft_strlen(tmp[0])))
			return (free_doubles(tmp), i);
		free_doubles(tmp);
	}
	return (-1);
}

int	re_init_env(t_vars *vars, int count, int del)
{
	char	**new_env;
	int		i;
	int		j;
	if (del == 0)
    	return (1);
	new_env = malloc(sizeof(char *) * (count - del + 1));
	if (!new_env)
		return (0);
	while (count >= ++i)
	{
		if (!vars->env[i])
			continue;
		new_env[++j] = ft_strdup(vars->env[i]);
		if (!new_env[j])
			return (free_doubles(new_env), 0);
	}
	free_doubles2((void **)vars->env, count);
	new_env[++j] = NULL;
	init_env(vars, new_env);
	free_doubles(new_env);
	return (1);
}
