#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_vars
{
    int     hist;
    int     i;
    char    *user_pwd;
	char    *input;
	char	*output;
	char	**input_parsed;
	char	**env;
	int		argc;
	int		exit_stat;
	int		origin_stdin;
	int		origin_stdout;
	int		file_opened;
	int		file_created;
}   t_vars;

int	err_msg(char *str);
int double_counter(char **str);
int init_env(t_vars *vars, char **env);
int free_doubles(char **str);
int null_free(char **str);
int reset_vars(t_vars *vars);
int reset_fds(t_vars *vars);

#endif