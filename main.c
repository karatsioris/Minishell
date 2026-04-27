#include "stdio.h"
#include "stdlib.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **envp)
{
    (void)envp;
    (void)argv;
    (void)argc;
    char *line;

    while (1)
    {
        line = readline("give_a_prompt> ");
        if (!line)
            break;
        if (line[0] != '\0')
            add_history(line);
        printf("%s\n", line);
        free(line);
    }
    return (0);
}
