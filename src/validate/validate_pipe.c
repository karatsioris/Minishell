#include "validate.h"
#include "token.h"

static t_syntax_error	check_pipe_at(const char *input, int i)
{
	int	next_non_space;
	int	first_non_space;

	next_non_space = skip_spaces(input, i + 1);
	first_non_space = skip_spaces(input, 0);
	if (input[next_non_space] == '|')
		return (SYNTAX_DOUBLE_PIPE);
	if (first_non_space == i)
		return (SYNTAX_PIPE_AT_START);
	if (input[next_non_space] == '\0')
		return (SYNTAX_PIPE_AT_END);
	return (SYNTAX_OK);
}

t_syntax_error	check_pipes(const char *input)
{
	int				i;
	t_quote_state	state;
	char			quote_char;
	t_syntax_error	err;

	i = 0;
	state = STATE_NONE;
	quote_char = '\0';
	while (input[i] != '\0')
	{
		update_quote_state(input[i], &state, &quote_char);
		if (state != STATE_NONE)
		{
			i++;
			continue ;
		}
		if (input[i] == '|')
		{
			err = check_pipe_at(input, i);
			if (err != SYNTAX_OK)
				return (err);
		}
		i++;
	}
	return (SYNTAX_OK);
}
