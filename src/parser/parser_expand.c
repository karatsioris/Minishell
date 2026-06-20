#include "parser_expand.h"

static int	append_literal(char **result, const char *value, int *index)
{
	char	literal[2];

	literal[0] = value[*index];
	literal[1] = '\0';
	*result = append_str(*result, literal);
	if (!*result)
		return (0);
	(*index)++;
	return (1);
}

char	*expand_token_value(const char *value, t_shell *shell,
		t_quote_state quote)
{
	char	*result;
	int		index;

	if (!value)
		return (NULL);
	if (quote == STATE_SINGLE || !shell)
		return (ft_strdup(value));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	index = 0;
	while (value[index])
	{
		if (value[index] != '$')
		{
			if (!append_literal(&result, value, &index))
				return (NULL);
			continue ;
		}
		result = expand_dollar(value, &index, shell, result);
		if (!result)
			return (NULL);
	}
	return (result);
}

int	apply_expansions(t_token *tokens, int count, t_shell *shell)
{
	int		index;
	int		new_count;
	char	*expanded;

	if (!tokens || !shell)
		return (count);
	index = 0;
	new_count = 0;
	while (index < count)
	{
		if (tokens[index].type == TOKEN_WORD && tokens[index].value)
		{
			expanded = expand_token_value(tokens[index].value, shell,
					tokens[index].quote);
			if (expanded)
			{
				free(tokens[index].value);
				tokens[index].value = expanded;
			}
			if (tokens[index].quote == STATE_NONE
				&& tokens[index].value[0] == '\0')
			{
				free(tokens[index].value);
				index++;
				continue ;
			}
		}
		if (new_count != index)
			tokens[new_count] = tokens[index];
		new_count++;
		index++;
	}
	return (new_count);
}
