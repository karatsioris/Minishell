#include "executer.h"

void	free_tokens(t_token *tokens, int count)
{
	int	index;

	if (!tokens)
		return;
	index = 0;
	while (index < count)
	{
		free(tokens[index].value);
		index++;
	}
	free(tokens);
}

static void	free_redirs(t_redir *redirs)
{
	t_redir	*next;

	while (redirs)
	{
		next = redirs->next;
		free(redirs->file);
		free(redirs);
		redirs = next;
	}
}

void	free_ast(t_node *node)
{
	int	index;

	if (!node)
		return;
	free_ast(node->left);
	free_ast(node->right);
	index = 0;
	if (node->args)
	{
		while (node->args[index])
		{
			free(node->args[index]);
			index++;
		}
		free(node->args);
	}
	free_redirs(node->redirs);
	free(node);
}