#ifndef TOKEN_H
# define TOKEN_H


void    tokenize(const char *input);


typedef	enum e_class
{
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_EOF,
} t_class;

typedef	enum e_kind
{
	OP_PIPE, // |
    OP_LOGIC, // && and ||
    OP_REDIRECT, // < , > , << , >>
    OP_GROUP, // ( and )
} t_operator_kind;


typedef struct s_token_descriptor
{
    const char        *text;
    t_operator_kind      kind;
    int         length;
} t_token_descriptor;

typedef struct s_token
{
	char	            *value;
	t_class	            type;
	const t_token_descriptor  *descriptor;
} t_token;

# endif