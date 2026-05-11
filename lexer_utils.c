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

int  is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

static const t_token_descriptor g_token_table[] =
{
    // text    kind          length
    {"|",      OP_PIPE,      1},
    {"<<",     OP_HEREDOC,  2},
    {"<",      OP_REDIR_IN,  1},
    {">>",     OP_APPEND,  2},
    {">",      OP_REDIR_OUT,  1},
    {"(",      OP_GROUP,     1},
    {")",      OP_GROUP,     1},
    {NULL,     0,            0}
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

void    scan_word_with_quotes(t_lexer *lexer)
{
    while(lexer->current_char != '\0')
    {
        if(lexer->current_char == '\'' && lexer->quote_state != STATE_DOUBLE)
        {
            if (lexer->quote_state == STATE_SINGLE)
                lexer->quote_state = STATE_NONE;
            else
                lexer->quote_state = STATE_SINGLE;
        }
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
        advance_lexer(lexer);
    }
}
