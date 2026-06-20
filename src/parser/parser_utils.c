/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:39:57 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/19 13:41:58 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	find_pipe(t_token *tokens, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		if (tokens[i].type == TOKEN_PIPE)
			return (i);
		i++;
	}
	return (-1);
}

t_redir_type	get_redir_type(t_token token)
{
	if (ft_strncmp(token.value, "<<", 2) == 0)
		return (HEREDOC);
	else if (ft_strncmp(token.value, ">>", 2) == 0)
		return (APPEND);
	else if (ft_strncmp(token.value, "<", 1) == 0)
		return (REDIR_IN);

	return (REDIR_OUT);
}

t_redir	*new_redir(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->next = NULL;
	return (redir);
}

void	add_redir_back(t_redir **list, t_redir *new)
{
	t_redir	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
