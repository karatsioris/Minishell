/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:19:00 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:19:01 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*expand_step(const char *raw, t_expand_ctx *ctx, t_shell *shell,
		char *result)
{
	if (is_open_or_close_quote(raw[ctx->index], ctx->state, ctx->quote_char))
	{
		update_quote_state(raw[ctx->index], &ctx->state, &ctx->quote_char);
		ctx->index++;
		return (result);
	}
	if (raw[ctx->index] == '$' && ctx->state != STATE_SINGLE && shell)
		return (expand_dollar(raw, &ctx->index, shell, result));
	if (!append_literal(&result, raw, &ctx->index))
		return (NULL);
	return (result);
}

char	*expand_token_value(const char *raw, t_shell *shell)
{
	char			*result;
	t_expand_ctx	ctx;

	if (!raw)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	ctx.index = 0;
	ctx.state = STATE_NONE;
	ctx.quote_char = '\0';
	while (raw[ctx.index])
	{
		result = expand_step(raw, &ctx, shell, result);
		if (!result)
			return (NULL);
	}
	return (result);
}

static int	expand_one_token(t_token *token, t_shell *shell)
{
	char	*expanded;

	expanded = expand_token_value(token->value, shell);
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
