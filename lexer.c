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

int		tokenize_operator(const char *input, t_token *tokens, int index, int i)
{
    const t_token_descriptor *desc = match_operator(&input[i]);
    if (desc)
    {
        tokens[index].type = TOKEN_OPERATOR;
        tokens[index].descriptor = desc;
        tokens[index].value = ft_substr(input, i, desc->length);
        return (desc->length);
    }
    return (0);
}

int		tokenize_word(const char *input, t_token *tokens, int index, int i)
{
    int start = i;

    while (input[i] && !is_space(input[i]) && !match_operator(&input[i]))
        i++;
    tokens[index].type = TOKEN_WORD;
    tokens[index].descriptor = NULL;
    tokens[index].value = ft_substr(input, start, i - start);
    return (i - start);
}

void	finalize_tokens(t_token *tokens, int index, int *token_count)
{
    tokens[index].value = NULL;
    tokens[index].type = TOKEN_EOF;
    tokens[index].descriptor = NULL;
    *token_count = index;
}

t_token *tokenize(const char *input, int *token_count)
{
    int index = 0, i = 0;
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
        if (match_operator(&input[i]))
            i += tokenize_operator(input, tokens, index, i);
        else
            i += tokenize_word(input, tokens, index, i);
        if (!tokens[index++].value)
            return (free_tokens(tokens, index - 1), NULL);
    }
 	finalize_tokens(tokens, index, token_count);
    return (tokens);
}
