/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:18:15 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:18:16 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "executer_internal.h"
#include "validate.h"

static int	open_redir_fd(t_redir *redir, t_shell *shell)
{
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == REDIR_OUT)
		return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == APPEND)
		return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (apply_heredoc(redir->file, redir->expand, shell));
}

static int	dup_redir_fd(t_redir *redir, int fd)
{
	if (redir->type == REDIR_IN || redir->type == HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
			return (1);
	}
	else if (dup2(fd, STDOUT_FILENO) < 0)
		return (1);
	return (0);
}

int	apply_redirections(t_node *node, t_shell *shell)
{
	t_redir	*redir;
	int		fd;

	redir = node->redirs;
	while (redir)
	{
		fd = open_redir_fd(redir, shell);
		if (fd < 0)
		{
			if (fd == -2)
				return (-2);
			perror(redir->file);
			return (1);
		}
		if (dup_redir_fd(redir, fd))
		{
			close(fd);
			return (1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}
