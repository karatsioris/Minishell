#include "token.h"

void	init_lexer(t_lexer *lexer, const char *input)
{
    if (!lexer)
        return ;
    lexer->input = input;
    lexer->pos = 0;
    if(input && input[0])
        lexer->current_char = input[0];
    else
        lexer->current_char = '\0';
    // lexer->quote_state = STATE_NONE;
}

t_token	create_eof_token()
{
     t_token	token;

    token.type = TOKEN_EOF;
    token.value = NULL;
    token.quote = STATE_NONE;
    return (token);
}
 
t_token tokenize_operator(t_lexer *lexer)
{
    t_token                     token;
    const t_token_descriptor    *desc;

    desc = match_operator(&lexer->input[lexer->pos]);
    if(!desc)
        return(create_eof_token());

    token.type = desc->type;
    token.value = ft_substr(lexer->input, lexer->pos, desc->length);
    token.quote = STATE_NONE;
    
    lexer->pos += desc->length;
    lexer->current_char = lexer->input[lexer->pos];
    return (token);
}
            
t_token     tokenize_word(t_lexer *lexer)
{
    int     start = lexer->pos;
    t_token token;
    token.type = TOKEN_WORD;
    token.quote = scan_word_for_quotes(lexer);
    token.value = ft_substr(lexer->input, start, lexer->pos - start);
    return (token);
}

t_token     tokenize(t_lexer  *lexer)
{
    while(lexer->current_char && is_space(lexer->current_char))
        advance_lexer(lexer);

    if(lexer->current_char == '\0')
        return(create_eof_token());

    if (match_operator(&lexer->input[lexer->pos]))
        return (tokenize_operator(lexer));
    return (tokenize_word(lexer));
}
