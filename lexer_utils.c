#include "token.h"

int  is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
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