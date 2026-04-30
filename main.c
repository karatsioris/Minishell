#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <readline/readline.h>
#include <readline/history.h>


#include "token.h"
#include "libft/libft.h"


typedef struct s_shell
{
	int		exit_code;
	int		running;
	char	*line;
	char	**envp;
} t_shell;

int	evaluate_input(char	*line, t_shell	*shell)
{
	if (ft_strncmp(line, "exit", 4) == 0)
	{
		shell->running = 0;
		return (shell->exit_code);
	}
	printf("Input: %s\n", line);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
    t_shell		shell;
	int			token_count;
	t_token		*tokens;
	int 		i;
    (void)envp;
    (void)argv;
    (void)argc;

	shell.exit_code = 0;
	shell.running = 1;
	shell.envp  = NULL;
	shell.line = NULL;

    while (shell.running)
    {
        shell.line = readline("minishell$ ");
		
        if (shell.line == NULL)
		{
			printf("exit\n");
			break;
		}
		if (shell.line[0] != '\0')
			add_history(shell.line);
		tokens = tokenize(shell.line, &token_count);
		if(tokens != NULL)
		{
			i = 0;
            while (i < token_count)
            {
                printf("token[%d] = %s\n", i, tokens[i].value);
                i++;
            }
            free_tokens(tokens, token_count);
		}
        shell.exit_code = evaluate_input(shell.line, &shell);
        free(shell.line);
		shell.line = NULL;
    }
    return (shell.exit_code);
}
