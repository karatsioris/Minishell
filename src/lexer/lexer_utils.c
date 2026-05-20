#include "token.h"

// void free_tokens(t_token *tokens, int used)
// {
//     int	i;

//     if (!tokens)
//         return ;
//     i = 0;
//     while (i < used)
//     {
//         free(tokens[i].value);
//         i++;
//     }
//     free(tokens);
// }

int  is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

static const t_token_descriptor g_token_table[] =
{
    // text    kind                 length
    {"<<",     TOKEN_HEREDOC,       2},
    {">>",     TOKEN_APPEND,        2},
    {"|",      TOKEN_PIPE,          1},
    {"<",      TOKEN_REDIR_IN,      1},
    {">",      TOKEN_REDIR_OUT,     1},
    {NULL,     TOKEN_EOF,           0}
};

const t_token_descriptor  *match_operator(const char *input)
{
    int i = 0;
    if (!input)
        return (NULL);
    while(g_token_table[i].text != NULL)
    {
       if (ft_strncmp(input, g_token_table[i].text, g_token_table[i].length) == 0)
            return (&g_token_table[i]);
        i++;
    }
    return (NULL);
}


void    advance_lexer(t_lexer  *lexer)
{
    if(lexer->input[lexer->pos])
        {
            lexer->pos++;
            lexer->current_char = lexer->input[lexer->pos];
        }
}

t_quote_state   scan_word(t_lexer *lexer)
{
    t_quote_state   state = STATE_NONE;
    t_quote_state   result = STATE_NONE;
    char            quote_char = '\0';

     while (lexer->current_char != '\0')
    {
        if (state == STATE_NONE && (is_space(lexer->current_char)
                || match_operator(&lexer->input[lexer->pos])))
            break ;
        if (result == STATE_NONE && is_opening_or_closing_quote(lexer->current_char, state, quote_char))
            result = return_quote_state(lexer->current_char);
        update_quote_state(lexer->current_char, &state, &quote_char);
        advance_lexer(lexer);
    }
    return (result);
}

int  count_tokens(const char *input)
{
    int i = 0;
    int count = 0;
    t_quote_state state = STATE_NONE;
    char            quote_char = '\0';

    while (input[i])
    {
        while (input[i] && is_space(input[i]))
            i++;
        if (!input[i])
            break ;
        const t_token_descriptor *desc = match_operator(&input[i]);
        if (desc)
            i += desc->length;
        else
        {
            while (input[i] && (state != STATE_NONE || (!is_space(input[i]) && !match_operator(&input[i]))))
            {
                update_quote_state(input[i], &state, &quote_char);
                i++;
            }
        }
        count++;
    }
    return (count);
}

