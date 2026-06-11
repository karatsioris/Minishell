#include "validate.h"
#include "token.h"
#include "shell.h"
#include <readline/readline.h>
#include <readline/history.h>

static const char *g_syntax_errors[] = {
	[SYNTAX_OK]                   = NULL,
	[SYNTAX_UNCLOSED_SINGLE_QUOTE] = "syntax error: unclosed single quote",
	[SYNTAX_UNCLOSED_DOUBLE_QUOTE] = "syntax error: unclosed double quote",
	[SYNTAX_PIPE_AT_START]        = "syntax error near unexpected token `|'",
	[SYNTAX_PIPE_AT_END]          = "syntax error near unexpected token `|'",
	[SYNTAX_DOUBLE_PIPE]          = "syntax error near unexpected token `||'",
	[SYNTAX_INVALID_OPERATOR]     = "syntax error near unexpected token",
};

int	skip_spaces(const char *input, int i)
{
	while (input[i] != '\0' && input[i] == ' ')
		i++;
	return (i);
}

t_syntax_error	check_pipes(const char *input)
{
	int	i;
	int	next_non_space;
	int	first_non_space;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|')
		{
			next_non_space = skip_spaces(input, i + 1);
			first_non_space = skip_spaces(input, 0);

			if (input[next_non_space] == '|')
				return (SYNTAX_DOUBLE_PIPE);
			else if (first_non_space == i)
				return (SYNTAX_PIPE_AT_START);
			else if (input[next_non_space] == '\0')
				return (SYNTAX_PIPE_AT_END);
		}
		i++;
	}
	return (SYNTAX_OK);
}

t_syntax_error	check_after_operator(const char *input, int i)
{
	int	next;

	next = skip_spaces(input, i);
	if (input[next] == '\0')
		return (SYNTAX_INVALID_OPERATOR);
	if (input[next] == '|')
		return (SYNTAX_INVALID_OPERATOR);
	if (input[next] == '>' || input[next] == '<')
		return (SYNTAX_INVALID_OPERATOR);
	return (SYNTAX_OK);
}

t_syntax_error	check_redirections(const char *input)
{
	int				i;
	t_syntax_error	err;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '>' && input[i + 1] == '>')
		{
			err = check_after_operator(input, i + 2);
			if (err != SYNTAX_OK)
				return (err);
			i += 2;
			continue ;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			err = check_after_operator(input, i + 2);
			if (err != SYNTAX_OK)
				return (err);
			i += 2;
			continue ;
		}
		else if (input[i] == '>')
		{
			err = check_after_operator(input, i + 1);
			if (err != SYNTAX_OK)
				return (err);
			i++;
			continue ;
		}
		else if (input[i] == '<')
		{
			err = check_after_operator(input, i + 1);
			if (err != SYNTAX_OK)
				return (err);
			i++;
			continue ;
		}
		i++;
	}
	return (SYNTAX_OK);
}

t_syntax_error	check_quotes(const char *input)
{
	t_quote_state	state;
	int				i;

	state = STATE_NONE;
	i = 0;
	while (input[i] != '\0')
	{
		if (state == STATE_NONE && input[i] == '"')
			state = STATE_DOUBLE;
		else if (state == STATE_DOUBLE && input[i] == '"')
			state = STATE_NONE;
		if (state == STATE_NONE && input[i] == '\'')
			state = STATE_SINGLE;
		else if (state == STATE_SINGLE && input[i] == '\'')
			state = STATE_NONE;
		i++;
	}
	if (state == STATE_DOUBLE)
		return (SYNTAX_UNCLOSED_DOUBLE_QUOTE);
	else if (state == STATE_SINGLE)
		return (SYNTAX_UNCLOSED_SINGLE_QUOTE);
	return (SYNTAX_OK);
}

t_syntax_error	validate_input(const char *input)
{
	t_syntax_error	err;

	if (!input)
		return (SYNTAX_OK);

	err = check_pipes(input);
	if (err != SYNTAX_OK)
		return (err);	
	err = check_redirections(input);
	if (err != SYNTAX_OK)
		return (err);	
	err = check_quotes(input);
	if (err != SYNTAX_OK)
		return (err);	

	return (SYNTAX_OK);
}

void	readline_and_validate(t_syntax_error	err, t_shell	shell)
{
	while (shell.running)
	{
		shell.line = readline("minishell$ ");
		if (shell.line == NULL)
			break ;
		err = validate_input(shell.line);
		if (err != SYNTAX_OK)
		{
			printf("minishell: %s\n", g_syntax_errors[err]);
			shell.exit_code = 258;
			free(shell.line);
			shell.line = NULL;
			continue ;
		}
		if (shell.line[0] != '\0')
			add_history(shell.line);
	}
}
