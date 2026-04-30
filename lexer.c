#include "token.h"
#include "libft/libft.h"
#include "stdio.h"
#include "stdlib.h"

// This file lexer (lexical analyzer) is tokenizes input by breaking it into meaningful units.

int  is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

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

void free_tokens(t_token *tokens, int used)
{
      int	i;

    if (!tokens)
        return ;
    i = 0;
    while (i < used)
    {
        free(tokens[i].value);
        i++;
    }
    free(tokens);
}

static const t_token_descriptor g_token_table[] =
{
    // text    kind          length
    {"|",      OP_PIPE,      1},
    {"<<",     OP_REDIRECT,  2},
    {"<",      OP_REDIRECT,  1},
    {">>",     OP_REDIRECT,  2},
    {">",      OP_REDIRECT,  1},
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

t_token *tokenize(const char *input, int *token_count)
{
    int i = 0;
    int index = 0;
    t_token *tokens;

    if (!input || !token_count)
        return (NULL);
    
    tokens = malloc(sizeof(t_token) * (count_tokens(input) + 1));
    if (!tokens)
        return (NULL);

    while (input[i])
    {
        while (input[i] && is_space(input[i]))
            i++;
        if (!input[i])
            break;

        const t_token_descriptor *desc = match_operator(&input[i]);
        if (desc)
        {
            tokens[index].type = TOKEN_OPERATOR;
            tokens[index].descriptor = desc;
            tokens[index].value = ft_substr(input, i, desc->length);
            i += desc->length;
        }
        else
        {
            int start = i;
            while (input[i] && !is_space(input[i]) && !match_operator(&input[i]))
                i++;
            tokens[index].type = TOKEN_WORD;
            tokens[index].descriptor = NULL;
            tokens[index].value = ft_substr(input, start, i - start);
        }
        if (!tokens[index++].value)
            return (free_tokens(tokens, index - 1), NULL);
    }
    tokens[index].value = NULL;
    tokens[index].type = TOKEN_EOF;
    tokens[index].descriptor = NULL;
    *token_count = index;
    return (tokens);
}
