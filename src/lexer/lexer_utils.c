#include "token.h"

static const	t_token_descriptor	g_token_table[] =
{
{"<<",	TOKEN_HEREDOC,		2},
{">>",	TOKEN_APPEND,		2},
{"|",	TOKEN_PIPE,			1},
{"<",	TOKEN_REDIR_IN,		1},
{">",	TOKEN_REDIR_OUT,	1},
{NULL,	TOKEN_EOF,			0}
};

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

const t_token_descriptor	*match_operator(const char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (NULL);
	while (g_token_table[i].text != NULL)
	{
		if (ft_strncmp(input, g_token_table[i].text,
				g_token_table[i].length) == 0)
			return (&g_token_table[i]);
		i++;
	}
	return (NULL);
}


void	advance_lexer(t_lexer *lexer)
{
	if (lexer->input[lexer->pos])
	{
		lexer->pos++;
		lexer->current_char = lexer->input[lexer->pos];
	}
}


t_quote_state	scan_word(t_lexer *lexer)
{
	t_quote_state	state;
	t_quote_state	result;
	char			quote_char;

	state = STATE_NONE;
	result = STATE_NONE;
	quote_char = '\0';

	while (lexer->current_char != '\0')
	{
		if (state == STATE_NONE
			&& (is_space(lexer->current_char)
				|| match_operator(&lexer->input[lexer->pos])))
			break ;
		if (result == STATE_NONE
			&& is_open_or_close_quote(lexer->current_char, state, quote_char))
			result = return_quote_state(lexer->current_char);
		update_quote_state(lexer->current_char, &state, &quote_char);
		advance_lexer(lexer);
	}
	return (result);
}

int	count_tokens(const char *input)
{
	int							i;
	int							count;
	t_quote_state				state;
	char						quote_char;
	const t_token_descriptor	*desc;

	i = 0;
	count = 0;
	state = STATE_NONE;
	quote_char = '\0';
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		desc = match_operator(&input[i]);
		if (desc)
			i += desc->length;
		else
		{
			while (input[i]
				&& (state != STATE_NONE
					|| (!is_space(input[i]) && !match_operator(&input[i]))))
			{
				update_quote_state(input[i], &state, &quote_char);
				i++;
			}
		}
		count++;
	}
	return (count);
}

