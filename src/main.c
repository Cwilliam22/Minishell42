#include "../include/minishell.h"

int main(void)
{
    char *input;

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
        add_history(input);
        free(input);
    }
}
