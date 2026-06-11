#include "token.h"

t_quote_state	return_quote_state(char quote_char)
{
	if (quote_char == '\'')
		return (STATE_SINGLE);
	else
		return (STATE_DOUBLE);
}

int	is_open_or_close_quote(char c, t_quote_state state, char quote_char)
{
	if (state == STATE_NONE && (c == '\'' || c == '"'))
		return (1);
	if ((state == STATE_DOUBLE || state == STATE_SINGLE) && c == quote_char)
		return (1);
	return (0);
}

void	update_quote_state(char c, t_quote_state *state, char *quote_char)
{
	if (*state == STATE_NONE && (c == '\'' || c == '"'))
	{
		*quote_char = c;
		*state = return_quote_state(c);
	}
	else if ((*state == STATE_DOUBLE || *state == STATE_SINGLE)
		&& c == *quote_char)
	{
		*state = STATE_NONE;
		*quote_char = '\0';
	}
}

char	*remove_quotes(const char *raw)
{
	char			*result;
	char			quote_char;
	int				i;
	int				j;
	t_quote_state	state;

	quote_char = '\0';
	i = 0;
	j = 0;
	state = STATE_NONE;
	result = malloc(ft_strlen(raw) + 1);

	if (!result)
		return (NULL);

	while (raw[i] != '\0')
	{
		if (!is_open_or_close_quote(raw[i], state, quote_char))
			result[j++] = raw[i];
		update_quote_state(raw[i], &state, &quote_char);
		i++;
	}
	result[j] = '\0';
	return (result);
}
