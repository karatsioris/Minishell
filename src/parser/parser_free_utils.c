#include "parse.h"


static void	free_redir(t_redir	*redirs)
{
	t_redir	*tmp;

	while(redirs != NULL)
	{
		tmp = redirs->next;
		free(redirs->file);
		redirs->file = NULL;
		free(redirs);
		tmp = redirs;
	}
}

void	free_ast(t_node *node)
{
	int	i;

	if (!node)
		return;
    free_ast(node->left);
    free_ast(node->right);
    free_redir(node->redirs);
    node->redirs = NULL;
    i = 0;
    if (node->args)
    {
        while (node->args[i])
        {
            free(node->args[i]);
            node->args[i] = NULL;
            i++;
        }
        free(node->args);
        node->args = NULL;
    }
    free(node);
}
