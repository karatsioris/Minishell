#include "validate.h"
#include "token.h"

static t_syntax_error	check_redir_op(const char *input, int i, int *next_i)
{
	t_syntax_error	err;

	if ((input[i] == '>' && input[i + 1] == '>')
		|| (input[i] == '<' && input[i + 1] == '<'))
	{
		err = check_after_operator(input, i + 2);
		*next_i = i + 2;
	}
	else
	{
		err = check_after_operator(input, i + 1);
		*next_i = i + 1;
	}
	return (err);
}

t_syntax_error	check_redirections(const char *input)
{
	int				i;
	t_syntax_error	err;
	t_quote_state	state;
	char			quote_char;

	i = 0;
	state = STATE_NONE;
	quote_char = '\0';
	while (input[i] != '\0')
	{
		update_quote_state(input[i], &state, &quote_char);
		if (state == STATE_NONE && (input[i] == '>' || input[i] == '<'))
		{
			err = check_redir_op(input, i, &i);
			if (err != SYNTAX_OK)
				return (err);
		}
		else
			i++;
	}
	return (SYNTAX_OK);
}
