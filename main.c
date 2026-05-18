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

static const char *g_syntax_errors[] = {
    [SYNTAX_OK]                   = NULL,
    [SYNTAX_UNCLOSED_SINGLE_QUOTE] = "syntax error: unclosed single quote",
    [SYNTAX_UNCLOSED_DOUBLE_QUOTE] = "syntax error: unclosed double quote",
    [SYNTAX_PIPE_AT_START]        = "syntax error near unexpected token `|'",
    [SYNTAX_PIPE_AT_END]          = "syntax error near unexpected token `--->|'",
    [SYNTAX_DOUBLE_PIPE]          = "syntax error near unexpected token `||'",
    [SYNTAX_INVALID_OPERATOR]     = "syntax error near unexpected token",
};


int skip_spaces(const char *input, int i)
{
	while (input[i] != '\0' && input[i] == ' ')
		i++;
    return (i);
}
t_syntax_error	check_pipes(const char *input)
{
	int i = 0;
	int find_char = skip_spaces(input, i);
	int find_char_end = skip_spaces(input , i + 1);
	printf("--> %d\n", find_char);
	while(input[i] != '\0')
	{
		if(input[find_char] == '|')
			return(SYNTAX_PIPE_AT_START);
		if(input[i] == '|')
		{
			int find_char_end = skip_spaces(input , i + 1);
			if(input[find_char_end] == '\0')
				return(SYNTAX_PIPE_AT_END);
		}
		i++;
	}
	return(SYNTAX_OK);
}

t_syntax_error  validate_input(const char *input)
{
	int i = 0;
	t_syntax_error err;


	if(!input)
		return (SYNTAX_OK);
	while (input[i] != '\0')
	{
		err = check_pipes(input);
			return(err);
		i++;
	}
	return(SYNTAX_OK);
}















int main(int argc, char **argv, char **envp)
{
    t_shell		shell;
	t_lexer		lexer;
	t_token		*all_token;
	int			token_count;
	t_syntax_error	err;

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
		err = validate_input(shell.line);
		if (err != SYNTAX_OK)
		{
			printf("minishell: %s\n", g_syntax_errors[err]);
			shell.exit_code = 258;
			free(shell.line);
		}
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
