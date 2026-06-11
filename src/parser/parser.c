#include "parse.h"
#include "token.h"
#include "shell.h"


t_token	*array_of_token(t_lexer *lexer, t_shell *shell, int *out_len)
{
	t_token	*all_token;
	int		num_tokens;
	int		i;

	(void)shell;
	i = 0;
	num_tokens = count_tokens(lexer->input);
	all_token = malloc(sizeof(t_token) *(num_tokens + 1));
	if (!all_token)
		return (NULL);
	while (i < num_tokens + 1)
	{
		all_token[i] = tokenize(lexer);
		i++;
	}
	if (out_len)
		*out_len = i;
	return (all_token);
}

t_node	*new_node(t_node_type type)
{
	t_node  *node = malloc(sizeof(t_node));

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

char	**build_args_array(t_token *tokens, int start, int end)
{
	char	**args;
	int		arg_count;
	int		i;
	int		j;

	i = start;
	arg_count = 0;
	while (i < end)
	{
		if (tokens[i].type != TOKEN_WORD)
			i++;
		else if (tokens[i].type == TOKEN_WORD)
			arg_count++;
		i++;
	}
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	j = 0;
	i = start;
	while ( i < end)
	{
		if (tokens[i].type == TOKEN_WORD)
			args[j++] = ft_strdup(tokens[i].value);
		else
			i++;
		i++;
	}
	args[j] = NULL;
	return (args);

}

t_redir	*build_redir_list(t_token *tokens, int start, int end)
{
	t_redir	*head;
	int		i;

	i = start;
	head = NULL;
	while (i < end)
	{
		if (tokens[i].type != TOKEN_WORD)
		{
			t_redir *r = new_redir(get_redir_type(tokens[i]), tokens[i + 1].value);
			add_redir_back(&head, r);
			i++;	// Skip filename
		}
		i++;
	}
	return (head);
}

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


t_node	*parse_token(t_token    *all_token, int count)
{
	if (!all_token || count <= 0)
		return (NULL);
	return (parse_subtokens(all_token, 0, count - 1));
}
