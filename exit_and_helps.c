#include "libft/libft.h"

int err_msg (char *str)
{
    ft_putendl_fd(str, 2);
    return (1);    
}

int null_free(char **str)
{
    if (!str)
        return (1);
    free(str);
    str = NULL;
    return (1);
}

int free_doubles(char **str)
{
    int i;

    if (!str)
        return (1);
    i = -1;
    while (str[++i])
        null_free((char **)&str[i]);
    free(str);
    return (1);
}

int free_doubles2(void **str, int n)
{
    int i;

    if (!str)
        return (1);
    i = -1;
    while (n > ++i)
        if (str[i] != NULL)
            null_free((char **)&str[i]);
    free(str);
    str = NULL;
    return (1);
}
