#ifndef PARSE_H
# define PARSE_H

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


# endif