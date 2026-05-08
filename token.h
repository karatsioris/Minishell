#ifndef TOKEN_H
# define TOKEN_H

#include "libft/libft.h"
#include "stdio.h"
#include "stdlib.h"


typedef enum e_quote_state
{
	STATE_NONE,
	STATE_SINGLE,
	STATE_DOUBLE,
} t_quote_state;


typedef	enum e_class
{
	TOKEN_WORD,	
	TOKEN_OPERATOR,
	TOKEN_EOF,
} t_class;

typedef	enum e_kind
{
	OP_PIPE, // |
    OP_REDIRECT, // < , > , << , >>
    OP_GROUP, // ( and )
} t_operator_kind;

typedef struct s_token_descriptor
{
	const char        *text;
    t_operator_kind      kind;
    int         length;
} t_token_descriptor;


//reading
typedef	struct s_lexer
{
	const char	*input;
	int			pos;
	char		current_char;
	t_quote_state	quote_state;
} t_lexer;

// results
typedef struct s_token
{
	char	            *value;
	t_class	            type;
	const t_token_descriptor  *descriptor;
	t_quote_state		quote;
} t_token;

t_token     tokenize(t_lexer  *lexer);
void		init_lexer(t_lexer *lexer, const char *input);
void 		free_tokens(t_token *tokens, int used);
const t_token_descriptor  *match_operator(const char *input);
int  is_space(char c);
void    scan_word_with_quotes(t_lexer *lexer);
void    advance_lexer(t_lexer  *lexer);
# endif