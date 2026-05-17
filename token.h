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

typedef enum e_token_type
{
	TOKEN_WORD,
    TOKEN_PIPE,      // |
    TOKEN_HEREDOC,   // <<
    TOKEN_REDIR_IN,  // <
    TOKEN_APPEND,    // >>
    TOKEN_REDIR_OUT, // >
    TOKEN_EOF
} t_token_type;

typedef struct s_token_descriptor
{
	const char		*text;
	t_token_type	type;
	int				length;
} t_token_descriptor;


//reading
typedef	struct s_lexer
{
	const char		*input;
	int				pos;
	char			current_char;
} t_lexer;

// results
typedef struct s_token
{
	char	            *value;
	t_token_type		type;
	t_quote_state		quote;
} t_token;

t_token     tokenize(t_lexer  *lexer);
void		init_lexer(t_lexer *lexer, const char *input);
void 		free_tokens(t_token *tokens, int used);
const t_token_descriptor  *match_operator(const char *input);
int  is_space(char c);
t_quote_state    scan_word_for_quotes(t_lexer *lexer);
void    advance_lexer(t_lexer  *lexer);
int 	count_tokens(const char *input);
# endif