/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:41:36 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/19 14:24:38 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static const t_token_descriptor	g_token_table[] = {
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

static int	skip_word(const char *input, int i)
{
	t_quote_state	state;
	char			quote_char;

	state = STATE_NONE;
	quote_char = '\0';
	while (input[i]
		&& (state != STATE_NONE
			|| (!is_space(input[i]) && !match_operator(&input[i]))))
	{
		update_quote_state(input[i], &state, &quote_char);
		i++;
	}
	return (i);
}

int	count_tokens(const char *input)
{
	int							i;
	int							count;
	const t_token_descriptor	*desc;

	i = 0;
	count = 0;
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
			i = skip_word(input, i);
		count++;
	}
	return (count);
}

