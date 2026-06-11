#include "token.h"

void	free_tokens(t_token *tokens, int count)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (i < count)
	{
		free(tokens[i].value);
		tokens[i].value = NULL;
		i++;
	}
	free (tokens);
}
