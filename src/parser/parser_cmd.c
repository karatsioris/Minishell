/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 13:28:32 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/19 13:37:12 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parse.h"

t_node	*cmd_node(t_token *tokens, int start, int end)
{
	t_node	*node;

	node = new_node(NODE_CMD);
	if (!node)
		return (NULL);

	node->args = build_args_array(tokens, start, end);
	node->redirs = build_redir_list(tokens, start, end);

	return (node);
}

static int	count_words(t_token *tokens, int start, int end)
{
	int	i;
	int	count;

	i = start;
	count = 0;
	while (i < end)
	{
		if (tokens[i].type == TOKEN_WORD)
			count++;
		i++;
	}
	return (count);
}

static char	**fill_args(t_token *tokens, int start, int end, char **args)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	while (i < end)
	{
		if (tokens[i].type == TOKEN_WORD)
			args[j++] = ft_strdup(tokens[i].value);
		i++;
	}
	args[j] = NULL;
	return (args);
}

char	**build_args_array(t_token *tokens, int start, int end)
{
	char	**args;
	int		arg_count;

	arg_count = count_words(tokens, start, end);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	return (fill_args(tokens, start, end, args));
}
