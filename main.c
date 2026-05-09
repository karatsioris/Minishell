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

// function that should be in the parser.c
t_token     *array_of_token(t_lexer *lexer, t_shell *shell, int *out_len)
{
	(void)shell;
	t_token		*all_token;
	int		num_tokens;
	int		i= 0;

	num_tokens = count_tokens(lexer->input);
	all_token = malloc(sizeof(t_token) *(num_tokens + 1));
	if (!all_token)
    	return (NULL);
    while(i < num_tokens)
	{
		all_token[i] = tokenize(lexer);
		if(all_token[i].type == TOKEN_EOF)
			break;
		i++;
	}
	if(out_len)
		*out_len = i;
	return(all_token);
}

void	print_tokens(t_token	*all_token, int count)
{
	int i = 0;
	while(i < count)
	{
		printf("Token %d: \'%s\' (%s)\n", i, all_token[i].value, token_type_to_string(all_token[i]));
            // free(all_token->value); // need to check for memory leaks
            i++;
	}
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
        shell.exit_code = evaluate_input(shell.line, &shell);
        free(shell.line);
		shell.line = NULL;
    }
    return (shell.exit_code);
}
