#include "parse.h"
#include "token.h"
#include "shell.h"

static char	*lookup_env_value(char **envp, const char *name, int name_len)
{
	int	i;

	if (!envp || !name || name_len <= 0)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

static char	*append_str(char *base, const char *suffix)
{
	char	*joined;

	if (!base || !suffix)
		return (NULL);
	joined = ft_strjoin(base, suffix);
	free(base);
	return (joined);
}

static char	*expand_token_value(const char *value, t_shell *shell, t_quote_state quote)
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
			char literal[2];

			literal[0] = value[index];
			literal[1] = '\0';
			result = append_str(result, literal);
			if (!result)
				return (NULL);
			index++;
			continue;
		}
		if (value[index + 1] == '?')
		{
			char status[32];

			snprintf(status, sizeof(status), "%d", shell->exit_code);
			result = append_str(result, status);
			if (!result)
				return (NULL);
			index += 2;
			continue;
		}
		if (value[index + 1] == '\0')
		{
			result = append_str(result, "$");
			if (!result)
				return (NULL);
			index++;
			continue;
		}
		if (value[index + 1] == '_' || ft_isalpha(value[index + 1]))
		{
			int	name_start;
			int	name_len;
			char	*env_value;

			name_start = index + 1;
			name_len = name_start;
			while (value[name_len] == '_' || ft_isalnum(value[name_len]))
				name_len++;
			env_value = lookup_env_value(shell->envp, value + name_start, name_len - name_start);
			result = append_str(result, env_value ? env_value : "");
			if (!result)
				return (NULL);
			index = name_len;
			continue;
		}
		result = append_str(result, "$");
		if (!result)
			return (NULL);
		index++;
	}
	return (result);
}

static int	apply_expansions(t_token *tokens, int count, t_shell *shell)
{
	int	index;
	int	new_count;

	if (!tokens || !shell)
		return (count);
	index = 0;
	new_count = 0;
	while (index < count)
	{
		if (tokens[index].type == TOKEN_WORD && tokens[index].value)
		{
			char *expanded;

			expanded = expand_token_value(tokens[index].value, shell, tokens[index].quote);
			if (expanded)
			{
				free(tokens[index].value);
				tokens[index].value = expanded;
				if (tokens[index].quote == STATE_NONE && expanded[0] == '\0')
				{
					free(tokens[index].value);
					index++;
					continue ;
				}
			}
		}
		if (new_count != index)
			tokens[new_count] = tokens[index];
		new_count++;
		index++;
	}
	return (new_count);
}


t_token     *array_of_token(t_lexer *lexer, t_shell *shell, int *out_len)
{
	t_token		*all_token;
	int		num_tokens;
	int		new_count;
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
	new_count = apply_expansions(all_token, num_tokens, shell);
	all_token[new_count] = all_token[num_tokens];
	if(out_len)
		*out_len = new_count + 1;
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

// void	build_args_array(t_node *node, t_token	*tokens, int start, int end)
// {
// 	int arg_count = 0;
// 	int i;

// 	i = start;
// 	while(i < end)
// 	{
// 		if (tokens[i].type != TOKEN_WORD)
//             i++;
// 		else if(tokens[i].type == TOKEN_WORD)
// 			arg_count++;
// 		i++;
// 	}
// 	node->args = malloc(sizeof(char *) * (arg_count + 1));
// 	if(!node->args)
// 		return;
// }

// void	populate_node_data(t_node *node, t_token	*tokens, int start, int end)
// {
// 	int i = start;
// 	int j = 0;
// 	while( i < end)
// 	{
// 		if (tokens[i].type != TOKEN_WORD)
//         {
//             t_redir *r = new_redir(get_redir_type(tokens[i]), tokens[i + 1].value);
//             add_redir_back(&(node->redirs), r);
//             i++; // Skip the filename token
//         }
//         else if (tokens[i].type == TOKEN_WORD)
//             node->args[j++] = ft_strdup(tokens[i].value);
//         i++;
// 	}
// 	node->args[j] = NULL;
// }

// t_node	*cmd_node(t_token *tokens, int start, int end)
// {
// 	t_node *node = new_node(NODE_CMD);
// 	if (!node)
//         return (NULL);
	
// 	build_args_array(node, tokens, start, end);
//     if (!node->args)
//     {
//         free(node);
//         return (NULL);
//     }

//     populate_node_data(node, tokens, start, end);
	
// 	return(node);
// }

char    **build_args_array(t_token *tokens, int start, int end)
{
	char	**args;
	int arg_count;
	int i;
	int j;

	i = start;
	arg_count = 0;
	while(i < end)
	{
		if (tokens[i].type != TOKEN_WORD)
			i++;
		else if(tokens[i].type == TOKEN_WORD)
			arg_count++;
		i++;
	}
	args = malloc(sizeof(char *) * (arg_count + 1));
	if(!args)
		return(NULL);
	j = 0;
	i = start;
	while( i < end)
	{
		if (tokens[i].type == TOKEN_WORD)
            args[j++] = ft_strdup(tokens[i].value);
		else
			i++;
        i++;
	}
	args[j] = NULL;
	return(args);

}

t_redir  *build_redir_list(t_token *tokens, int start, int end)
{
	t_redir *head = NULL;
    int i = start;

    while (i < end)
    {
        if (tokens[i].type != TOKEN_WORD)
        {
            t_redir *r = new_redir(get_redir_type(tokens[i]), tokens[i + 1].value);
            add_redir_back(&head, r);
            i++; // Skip filename
        }
        i++;
    }
    return (head);
}

t_node   *cmd_node(t_token *tokens, int start, int end)
{
    t_node *node = new_node(NODE_CMD);
    if (!node)
        return (NULL);

    node->args = build_args_array(tokens, start, end);
    node->redirs = build_redir_list(tokens, start, end);

    return (node);
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
