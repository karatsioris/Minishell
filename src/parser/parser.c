/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:39:44 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/19 13:41:52 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "token.h"
#include "shell.h"
#include "parser_expand.h"

t_token	*array_of_token(t_shell *shell, int *out_len)
{
	t_lexer		lexer;
	t_token		*all_token;
	int			num_tokens;
	int			new_count;
	int			i;
	const char	*input;

	i = 0;
	input = shell->line;
	init_lexer(&lexer, input);
	num_tokens = count_tokens(lexer.input);
	all_token = malloc(sizeof(t_token) * (num_tokens + 1));
	if (!all_token)
		return (NULL);
	while (i < num_tokens + 1)
	{
		all_token[i] = tokenize(&lexer);
		i++;
	}
	new_count = apply_expansions(all_token, num_tokens, shell);
	all_token[new_count] = all_token[num_tokens];
	if (out_len)
		*out_len = new_count + 1;
	return (all_token);
}

t_node	*new_node(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->redirs = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_redir	*build_redir_list(t_token *tokens, int start, int end)
{
	t_redir	*head;
	t_redir	*r;
	int		i;

	i = start;
	head = NULL;
	while (i < end)
	{
		if (tokens[i].type != TOKEN_WORD)
		{
			r = new_redir(get_redir_type(tokens[i]),
					tokens[i + 1].value);
			add_redir_back(&head, r);
			i++;	// Skip filename
		}
		i++;
	}
	return (head);
}


t_node	*parse_subtokens(t_token *tokens, int start, int end)
{
	int		pipe_index;
	t_node	*root;

	if (start >= end)
		return (NULL);
	pipe_index = find_pipe(tokens, start, end);

	if (pipe_index >= 0)
	{
		root = new_node(NODE_PIPE);
		if (!root)
			return (NULL);
		root->left = parse_subtokens(tokens, start, pipe_index);
		root->right = parse_subtokens(tokens, pipe_index + 1, end);
		return (root);
	}
	return (cmd_node(tokens, start, end));
}


t_node	*parse_token(t_token *all_token, int count)
{
	if (!all_token || count <= 0)
		return (NULL);
	return (parse_subtokens(all_token, 0, count - 1));
}
