#include "parse.h"

char	*token_type_to_string(t_token token)
{
	if (token.type == TOKEN_WORD)
		return ("WORD");
	else if (token.type == TOKEN_PIPE)
		return ("PIPE");
    else if (token.type == TOKEN_HEREDOC)
		return ("HEREDOC");
    else if (token.type == TOKEN_REDIR_IN)
		return ("REDIR_IN");
    else if (token.type == TOKEN_APPEND)
		return ("TOKEN_APPEND");
    else if (token.type == TOKEN_REDIR_OUT)
		return ("REDIR_OUT");
	else if (token.type == TOKEN_EOF)
		return ("EOF");
	return (NULL);
}

void	print_tokens(t_token	*all_token, int count)
{
	int i = 0;
	while(i < count)
	{
		printf("Token %d: \'%s\' (%s)\n", i, all_token[i].value, token_type_to_string(all_token[i]));
            i++;
	}
}

void print_redirs(t_redir *redir)
{
    while (redir)
    {
        char *type;
        if (redir->type == REDIR_IN) type = "<";
        else if (redir->type == REDIR_OUT) type = ">";
        else if (redir->type == APPEND) type = ">>";
        else type = "<<";

        printf(" [%s %s]", type, redir->file);
        redir = redir->next;
    }
}

void print_ast(t_node *node, int level, const char *label)
{
    if (node == NULL)
        return;

    print_ast(node->right, level + 1, "R---");

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
	else if (node->type == NODE_CMD)
	{
        printf("[CMD: ");
        if (node->args)
		{
            for (int i = 0; node->args[i] != NULL; i++)
                printf(" %s", node->args[i]);
        }
		if (node->redirs)
        {
            printf(" {Redirs:");
            print_redirs(node->redirs);
            printf("}");
        }
        printf("]\n");
    }

    print_ast(node->left, level + 1, "L---");
}
