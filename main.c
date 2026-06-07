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
#include "executer.h"
#include "builtin.h"
#include "signals.h"



static const char *g_syntax_errors[] = {
    [SYNTAX_OK]                   = NULL,
    [SYNTAX_UNCLOSED_SINGLE_QUOTE] = "syntax error: unclosed single quote",
    [SYNTAX_UNCLOSED_DOUBLE_QUOTE] = "syntax error: unclosed double quote",
    [SYNTAX_PIPE_AT_START]        = "syntax error near unexpected token `|'",
    [SYNTAX_PIPE_AT_END]          = "syntax error near unexpected token `|'",
    [SYNTAX_DOUBLE_PIPE]          = "syntax error near unexpected token `||'",
    [SYNTAX_INVALID_OPERATOR]     = "syntax error near unexpected token",
};

int main(int argc, char **argv, char **envp)
{
    t_shell		shell;
	t_lexer		lexer;
	t_token		*all_token;
	t_node		*ast;
	int			token_count;
	t_syntax_error	err;

    (void)envp;
    (void)argv;
    (void)argc;
	shell.exit_code = 0;
	shell.running = 1;
	shell.envp  = dup_envp(envp);
	if (!shell.envp)
	{
		write(STDERR_FILENO, "minishell: failed to copy environment\n", 38);
		return (1);
	}
	shell.line = NULL;
	all_token = NULL;
	ast = NULL;
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	setup_interactive_signals();

    while (shell.running)
    {
		signal_reset();
        shell.line = readline("minishell$ ");
		
		if (shell.line == NULL || (signal_was_interrupted() && shell.line[0] == '\0'))
		{
			if (signal_was_interrupted())
			{
				shell.exit_code = 130;
				signal_reset();
				free(shell.line);
				shell.line = NULL;
				continue;
			}
			break;
		}
		err = validate_input(shell.line);
		if (err != SYNTAX_OK)
		{
			printf("minishell: %s\n", g_syntax_errors[err]);
			shell.exit_code = 258;
			free(shell.line);
			shell.line = NULL;
			continue;
		}
		if (shell.line[0] != '\0')
			add_history(shell.line);        

		init_lexer(&lexer, shell.line);
		all_token = array_of_token(&lexer, &shell, &token_count);
		print_tokens(all_token, token_count);
		
		printf("\n\n\n");
		ast = parse_token(all_token, token_count);
		setup_execution_signals();
		shell.exit_code = execute_ast(ast, &shell);
		setup_interactive_signals();
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
	free_envp(shell.envp);
	shell.envp = NULL;
    return (shell.exit_code);
}
