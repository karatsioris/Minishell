#include "token.h"
#include "libft/libft.h"
#include "stdio.h"
#include "stdlib.h"

// This file lexer (lexical analyzer) is tokenizes input by breaking it into meaningful units.

int  is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

int  count_words(const char *input)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (input[i])
    {
        while (input[i] && is_space(input[i]))
            i++;
        if (!input[i])
            break ;
        count++;
        while (input[i] && !is_space(input[i]))
            i++;
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

t_token    *tokenize(const char *input, int *token_count)
{
    int     i;
    int     start;
    int     len;
    int     index;
    int     total_words;
    t_token *tokens;

    if (!input || !token_count)
        return (NULL);
    total_words = count_words(input);
    tokens = malloc(sizeof(t_token) * (total_words + 1));
    if (!tokens)
        return (NULL);
    i = 0;
    index = 0;
    while (input[i])
    {
        while (input[i] && is_space(input[i]))
            i++;
        if (!input[i])
            break ;
        start = i;
        while (input[i] && !is_space(input[i]))
            i++;
        len = i - start;
        tokens[index].value = ft_substr(input, start, len);
        if (!tokens[index].value)
        {
            free_tokens(tokens, index);
            return (NULL);
        }
        tokens[index].type = TOKEN_WORD;
        tokens[index].descriptor = NULL;
        index++;
    }
    tokens[index].value = NULL;
    tokens[index].type = TOKEN_EOF;
    tokens[index].descriptor = NULL;
    *token_count = index;
    return (tokens);
}
