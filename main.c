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

char	*token_type_to_string(t_token token)
{
	if (token.type == TOKEN_WORD)
		return ("WORD");
	else if (token.type == TOKEN_OPERATOR)
		return ("OPERATOR");
	else if (token.type == TOKEN_EOF)
		return ("EOF");
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
    t_shell		shell;
	t_lexer		lexer;
	t_token		token;
	int 		i = 0;

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
			break;

		if (shell.line[0] != '\0')
			add_history(shell.line);
		init_lexer(&lexer, shell.line);
		while (shell.running)
        {
            token = tokenize(&lexer);
            if (token.type == TOKEN_EOF)
                break ;
            printf("Token %d: \'%s\' (%s)\n", i, token.value, token_type_to_string(token));
            free(token.value);
            i++;
        }
        shell.exit_code = evaluate_input(shell.line, &shell);
        free(shell.line);
		shell.line = NULL;
    }
    return (shell.exit_code);
}
