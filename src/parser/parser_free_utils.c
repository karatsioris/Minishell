/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:40:48 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/18 14:40:50 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_redir(t_redir	*redirs)
{
	t_redir	*tmp;

	while (redirs != NULL)
	{
		tmp = redirs->next;
		free(redirs->file);
		redirs->file = NULL;
		free(redirs);
		redirs = tmp;
	}
}

void	free_ast(t_node *node)
{
	int	i;

	if (!node)
		return ;
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
	free (node);
}
