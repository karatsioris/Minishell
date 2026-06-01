#include "parse.h"
#include "token.h"
#include "shell.h"


t_token     *array_of_token(t_lexer *lexer, t_shell *shell, int *out_len)
{
	(void)shell;
	t_token		*all_token;
	int		num_tokens;
	int		i= 0;

	num_tokens = count_tokens(lexer->input);
	all_token = malloc(sizeof(t_token) *(num_tokens + 1));
	if (!all_token)
    	return (NULL);
    while(i < num_tokens + 1)
	{
		all_token[i] = tokenize(lexer);
		// if(all_token[i].type == TOKEN_EOF)
		// 	break;
		i++;
	}
	if(out_len)
		*out_len = i;
	return(all_token);
}

t_node  *new_node(t_node_type type)
{
    t_node  *node = malloc(sizeof(t_node));
    if(!node)
        return(NULL);
    node->type = type;
    node->args = NULL;
    node->redirs = NULL;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

t_node	*cmd_node(t_token *tokens, int start, int end)
{
	t_node *node = new_node(NODE_CMD);
	int arg_count = 0;
	int i;

	i = start;
	while(i < end)
	{
		if (tokens[i].type != TOKEN_WORD)
            i++;
		if(tokens[i].type == TOKEN_WORD)
			arg_count++;
		i++;
	}
	if(!node)
		return(NULL);
	node->args = malloc(sizeof(char *) * (arg_count + 1));
	if(!node->args)
		return(NULL);

	int j = 0;
	i = start;
	while( i < end)
	{
		if (tokens[i].type != TOKEN_WORD)
        {
            t_redir *r = new_redir(get_redir_type(tokens[i]), tokens[i + 1].value);
            add_redir_back(&(node->redirs), r);
            i++; // Skip the filename token
        }
        else if (tokens[i].type == TOKEN_WORD)
            node->args[j++] = ft_strdup(tokens[i].value);
        i++;
	}
	node->args[j] = NULL;
	return(node);
}

t_node	*parse_subtokens(t_token *tokens, int start, int end)
{
	int pipe_index;
	if(start >= end)
		return(NULL);
	pipe_index = find_pipe(tokens, start, end);

	if(pipe_index >= 0)
	{
		t_node *root = new_node(NODE_PIPE);
		if(!root)
			return(NULL);
		root->left = parse_subtokens(tokens, start, pipe_index);
		root->right = parse_subtokens(tokens, pipe_index + 1, end);
		return(root);
	}
	return(cmd_node(tokens, start, end));
}

t_node  *parse_token(t_token    *all_token, int count)
{
	 if (!all_token || count <= 0)
        return (NULL);
    return parse_subtokens(all_token, 0, count - 1);
}
// 