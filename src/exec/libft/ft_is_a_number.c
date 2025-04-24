
#include "includes/libft.h"

int ft_is_a_number(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (!ft_isdigit((int)arg[i]))
            return (0);
        i++;
    }
    return (1);
}