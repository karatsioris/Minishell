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

static int	expand_one_token(t_token *token, t_shell *shell)
{
	char	*expanded;

	expanded = expand_token_value(token->value, shell, token->quote);
	if (expanded)
	{
		free(token->value);
		token->value = expanded;
	}
	if (token->quote == STATE_NONE && token->value[0] == '\0')
	{
		free(token->value);
		return (0);
	}
	return (1);
}

int	apply_expansions(t_token *tokens, int count, t_shell *shell)
{
	int	index;
	int	new_count;

	if (!tokens || !shell)
		return (count);
	index = 0;
	new_count = 0;
	while (index < count)
	{
		if (tokens[index].type == TOKEN_WORD && tokens[index].value
			&& !expand_one_token(&tokens[index], shell))
		{
			index++;
			continue ;
		}
		if (new_count != index)
			tokens[new_count] = tokens[index];
		new_count++;
		index++;
	}
	return (new_count);
}
