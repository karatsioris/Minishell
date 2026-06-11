#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <readline/readline.h>
#include <readline/history.h>


#include "token.h"
#include "libft/libft.h"

#include "shell.h"
#include "parse.h"
#include "validate.h"

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

void initialization(t_shell	shell)
{
	t_lexer			lexer;
	t_token			*all_token;
	int				token_count;
	t_syntax_error	err;
	t_node			*ast;

	shell.exit_code = 0;
	shell.running = 1;
	shell.envp = NULL;
	shell.line = NULL;
	all_token = NULL;
	ast = NULL;
	err = SYNTAX_OK;
}

int	main(int argc, char **argv, char **envp)
{
    t_shell		shell;
	t_lexer			lexer;
	t_token			*all_token;
	int				token_count;
	t_syntax_error	err;
	t_node			*ast;
    (void)envp;
    (void)argv;
    (void)argc;

	initialization(shell);

    while (shell.running)
	{
		readline_and_validate(err, shell);
		init_lexer(&lexer, shell.line);
		all_token = array_of_token(&lexer, &shell, &token_count);
		print_tokens(all_token, token_count);
		
		printf("\n\n\n");
		ast = parse_token(all_token, token_count);
		print_ast(ast, 0, "ROOT");
		
        shell.exit_code = evaluate_input(shell.line, &shell);
		free_tokens(all_token, token_count);
		all_token = NULL;
		free_ast(ast);
		ast = NULL;
        free(shell.line);
		shell.line = NULL;
	}
	free_tokens(all_token, token_count);
	all_token = NULL;
	free_ast(ast);
	ast = NULL;
	free(shell.line);
	shell.line = NULL;
	return (shell.exit_code);
}
