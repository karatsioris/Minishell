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
t_quote_state   return_quote_state(char quote_char)
{
    if (quote_char == '\'')
        return  STATE_SINGLE;
    else
        return STATE_DOUBLE;
}

t_quote_state   scan_word(t_lexer *lexer)
{
    t_quote_state   state = STATE_NONE;
    t_quote_state   result = STATE_NONE;
    char            quote_char = '\0';

    while (lexer->current_char != '\0')
    {
        if (state == STATE_NONE && (lexer->current_char == '\''
                || lexer->current_char == '"'))
        {
            quote_char = lexer->current_char;
            result = return_quote_state(quote_char);
            state = result;
        }
        else if (state != STATE_NONE && lexer->current_char == quote_char)
            state = STATE_NONE;
        else if (state == STATE_NONE && (is_space(lexer->current_char)
                || match_operator(&lexer->input[lexer->pos])))
            break ;
        advance_lexer(lexer);
    }
    return (result);
}

char    *remove_quotes(const char *raw)
{
    char            *result;
    char            quote_char = '\0';
    int             i = 0, j = 0;
    t_quote_state   state = STATE_NONE;

    result = malloc(ft_strlen(raw) + 1);
    if (!result)
        return (NULL);

    while (raw[i] != '\0')
    {
        if (state == STATE_NONE && (raw[i] == '\'' || raw[i] == '"'))
        {
            quote_char = raw[i];
            state = return_quote_state(quote_char);
        }
        else if (state != STATE_NONE && raw[i] == quote_char)
            state = STATE_NONE;
        else
            result[j++] = raw[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}
