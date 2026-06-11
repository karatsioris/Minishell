#ifndef TOKEN_H
# define TOKEN_H

#include "libft.h"
#include "stdio.h"
#include "stdlib.h"


typedef enum e_quote_state
{
	STATE_NONE,
	STATE_SINGLE,
	STATE_DOUBLE,
}	t_quote_state;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,	// |
	TOKEN_HEREDOC,	// <<
	TOKEN_REDIR_IN,	// <
	TOKEN_APPEND,	// >>
	TOKEN_REDIR_OUT,	// >
	TOKEN_EOF
}	t_token_type;

typedef struct s_token_descriptor
{
	const char		*text;
	t_token_type	type;
	int				length;
}	t_token_descriptor;


//reading
typedef struct s_lexer
{
	const char		*input;
	int				pos;
	char			current_char;
}	t_lexer;

// results
typedef struct s_token
{
	char				*value;
	t_token_type		type;
	t_quote_state		quote;
}	t_token;

// lexer.c
void						init_lexer(t_lexer *lexer, const char *input);
t_token						create_eof_token(void);
t_token						tokenize_operator(t_lexer *lexer);
t_token						tokenize_word(t_lexer *lexer);
t_token						tokenize(t_lexer *lexer);

// lexer_free_utils.c
void						free_tokens(t_token *tokens, int count);

// lexer_utils.c
const t_token_descriptor	*match_operator(const char *input);
int							is_space(char c);
t_quote_state				scan_word(t_lexer *lexer);
void						advance_lexer(t_lexer *lexer);
int							count_tokens(const char *input);

// lexer_quotes.c
t_quote_state				return_quote_state(char quote_char);
int							is_open_or_close_quote(char c, t_quote_state state,
								char quote_char);
void						update_quote_state(char c, t_quote_state *state,
								char *quote_char);
char						*remove_quotes(const char *raw);

# endif