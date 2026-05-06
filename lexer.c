#include "token.h"

int  count_tokens(const char *input)
{
    int i = 0;
    int count = 0;

    while (input[i])
    {
        while (input[i] && is_space(input[i]))
            i++;
        if (!input[i])
            break ;

        const t_token_descriptor *desc = match_operator(&input[i]);
        if (desc)
        {
            i += desc->length;
        }
        else
        {
            while (input[i] && !is_space(input[i]) && !match_operator(&input[i]))
                i++;
        }
        count++;
    }
    return (count);
}



t_token	finalize_tokens()
{
     t_token	token;

    token.type = TOKEN_EOF;
    token.value = NULL;
    token.descriptor = NULL;
    token.quote = STATE_NONE;
    return (token);
}
 
t_token tokenize_operator(t_lexer *lexer)
{
    t_token					token;
    const t_token_descriptor	*desc;

    desc = match_operator(&lexer->input[lexer->pos]);
    token.type = TOKEN_EOF;
    token.value = NULL;
    token.descriptor = NULL;
    token.quote = STATE_NONE;
    if (!desc)
        return (token);
    token.type = TOKEN_OPERATOR;
    token.descriptor = desc;
    token.value = ft_substr(lexer->input, lexer->pos, desc->length);
    lexer->pos += desc->length;
    lexer->current_char = lexer->input[lexer->pos];
    return (token);
}
            
t_token     tokenize_word(t_lexer *lexer)
{
    int start = lexer->pos;
    t_token token;
    token.quote = STATE_NONE;

    while(lexer->current_char != '\0')
    {
        // state single_quote
        if(lexer->current_char == '\'' && lexer->quote_state != STATE_DOUBLE)
        {
            if (lexer->quote_state == STATE_SINGLE)
                lexer->quote_state = STATE_NONE;
            else
                lexer->quote_state = STATE_SINGLE;
        }
        // state double_quote
        else if (lexer->current_char == '\"' && lexer->quote_state != STATE_SINGLE)
        {
            if (lexer->quote_state == STATE_DOUBLE)
                lexer->quote_state = STATE_NONE;
            else
                lexer->quote_state = STATE_DOUBLE;
        }

        if (lexer->quote_state == STATE_NONE)
        {
            if (is_space(lexer->current_char) || match_operator(&lexer->input[lexer->pos]))
                break;
        }

        if(lexer->input[lexer->pos])
        {
            lexer->pos++;
            lexer->current_char = lexer->input[lexer->pos];
        }
    }
    token.type = TOKEN_WORD;
    token.descriptor = NULL;
    token.value = ft_substr(lexer->input, start, lexer->pos - start);
    return (token);
}

void	init_lexer(t_lexer *lexer, const char *input)
{
    if (!lexer)
        return ;
    lexer->input = input;
    lexer->pos = 0;
    lexer->current_char = (input && input[0]) ? input[0] : '\0';
    lexer->quote_state = STATE_NONE;
}

t_token     tokenize(t_lexer  *lexer)
{
    while(lexer->current_char && is_space(lexer->current_char))
    {
        if(lexer->input[lexer->pos])
        {
            lexer->pos++;
            lexer->current_char = lexer->input[lexer->pos];
        }
    }
    if(lexer->current_char == '\0')
        return(finalize_tokens());

    if (lexer->quote_state == STATE_NONE
        && match_operator(&lexer->input[lexer->pos]))
        return (tokenize_operator(lexer));
    return (tokenize_word(lexer));
}