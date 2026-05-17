#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <readline/readline.h>
#include <readline/history.h>


#include "token.h"
#include "libft/libft.h"

#include "shell.h"
#include "parse.h"

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
	t_lexer		lexer;
	t_token		*all_token;
	int			token_count;

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
		all_token = array_of_token(&lexer, &shell, &token_count);
		print_tokens(all_token, token_count);
		
		// printf("\n\n\n");
		// t_node *ast = parse_token(all_token, token_count);
		// print_ast(ast, 0, "ROOT");

        shell.exit_code = evaluate_input(shell.line, &shell);
        free(shell.line);
		shell.line = NULL;
    }
    return (shell.exit_code);
}
