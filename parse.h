#ifndef PARSE_H
# define PARSE_H

#include "token.h"
#include "shell.h"

typedef enum e_node_type
{
    NODE_CMD,
    NODE_PIPE,
    NODE_REDIR_OUT
}   t_node_type;

typedef struct s_node
{
    t_node_type type;
    char        **args;
    char        *files;
    struct s_node *left;
    struct s_node *right;
} t_node;

t_token     *array_of_token(t_lexer *lexer, t_shell *shell, int *out_len);
void        print_tokens(t_token	*all_token, int count);
t_node  *parse_token(t_token    *all_token, int count);
// void	print_ast(t_node *node, int depth);
void print_ast(t_node *node, int level, const char *label);
# endif