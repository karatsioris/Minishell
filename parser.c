#include "parse.h"
#include "token.h"
#include "shell.h"


char	*token_type_to_string(t_token token)
{
	if (token.type == TOKEN_WORD)
		return ("WORD");
	else if (token.type == TOKEN_OPERATOR)
		return ("OPERATOR");
	else if (token.type == TOKEN_EOF)
		return ("EOF");
	return (NULL);
}

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

void	print_tokens(t_token	*all_token, int count)
{
	int i = 0;
	while(i < count)
	{
		printf("Token %d: \'%s\' (%s)\n", i, all_token[i].value, token_type_to_string(all_token[i]));
            // free(all_token->value); // need to check for memory leaks
            i++;
	}
}

t_node  *new_node(t_node_type type)
{
    t_node  *node = malloc(sizeof(t_node));
    if(!node)
        return(NULL);
    node->type = type;
    node->args = NULL;
    node->files = NULL;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

t_node	*cmd_node(t_token *tokens, int start, int end)
{
	t_node *node;
	char **args;
	int count;
	int i;
	int j;

	count = 0;
	i = start;
	while(i < end)
	{
		if(tokens->type == TOKEN_WORD)
			count++;
		i++;
	}
	node = new_node(NODE_CMD);
	if(!node)
		return(NULL);
	args = malloc(sizeof(char *) * (count + 1));
	if(!args)
		return(NULL);

	j = 0;
	i = start;
	while( i < end)
	{
		if (tokens[i].type == TOKEN_WORD)
			args[j++] = ft_strdup(tokens[i].value);
		i++;
	}
	args[j] = NULL;
	node->args = args;
	return(node);
}

int find_pipe(t_token *tokens, int start, int end)
{
	int i = start;
	while(i < end)
	{
		if(tokens[i].type == TOKEN_OPERATOR && tokens[i].descriptor
            && tokens[i].descriptor->kind == OP_PIPE)
			return(i);
		i++;
	}
	return(-1);
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


void print_ast(t_node *node, int level, const char *label)
{
    if (node == NULL)
        return;

    print_ast(node->left, level + 1, "L---");

    // Print indentation with tree lines
    for (int i = 0; i < level; i++) {
        printf("│   ");
    }

    // Print the branch connector
    if (label && strcmp(label, "Root") != 0)
	{
        printf("├── %s(lvl %d) ", label, level);
    }
	else
	{
        printf("%s(lvl %d) ", label ? label : "", level);
    }

    if (node->type == NODE_PIPE)
	{
        printf("[PIPE]\n");
    }
	else if (node->type == NODE_REDIR_OUT)
	{
        printf("[> %s]\n", node->files ? node->files : "(no file)");
    }
	else if (node->type == NODE_CMD)
	{
        printf("[CMD");
        if (node->args)
		{
            for (int i = 0; node->args[i] != NULL; i++)
                printf(" %s", node->args[i]);
        }
        printf("]\n");
    }

    print_ast(node->right, level + 1, "R---");
}
