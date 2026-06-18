/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:25:01 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/18 16:29:53 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validate.h"
#include "token.h"

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
		if ((input[i] == '>' && input[i + 1] == '>')
			|| (input[i] == '<' && input[i + 1] == '<'))
		{
			err = check_after_operator(input, i + 2);
			if (err != SYNTAX_OK)
				return (err);
			i += 2;
		}
		else if (input[i] == '>' || input[i] == '<')
		{
			err = check_after_operator(input, i + 1);
			if (err != SYNTAX_OK)
				return (err);
			i++;
		}
		else
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
