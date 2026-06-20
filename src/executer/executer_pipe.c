/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:18:10 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:18:11 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>

#include "executer_internal.h"

static pid_t	spawn_left(t_node *node, t_shell *shell, t_fds fds,
		int *pipefd)
{
	pid_t	pid;
	t_fds	inner;

	pid = fork();
	if (pid != 0)
		return (pid);
	setup_child_signals();
	if (fds.in != STDIN_FILENO)
	{
		dup2(fds.in, STDIN_FILENO);
		close(fds.in);
	}
	if (pipefd[1] != STDOUT_FILENO)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	close(pipefd[0]);
	inner.in = STDIN_FILENO;
	inner.out = STDOUT_FILENO;
	_exit(execute_node(node, shell, inner, 0));
}

static pid_t	spawn_right(t_node *node, t_shell *shell, t_fds fds,
		int *pipefd)
{
	pid_t	pid;
	t_fds	inner;

	pid = fork();
	if (pid != 0)
		return (pid);
	setup_child_signals();
	if (pipefd[0] != STDIN_FILENO)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	if (fds.out != STDOUT_FILENO)
	{
		dup2(fds.out, STDOUT_FILENO);
		close(fds.out);
	}
	close(pipefd[1]);
	inner.in = STDIN_FILENO;
	inner.out = STDOUT_FILENO;
	_exit(execute_node(node, shell, inner, 0));
}

int	run_pipe_node(t_node *node, t_shell *shell, t_fds fds)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipefd) < 0)
		return (1);
	left_pid = spawn_left(node->left, shell, fds, pipefd);
	if (left_pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (1);
	}
	right_pid = spawn_right(node->right, shell, fds, pipefd);
	if (right_pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(left_pid, NULL, 0);
		return (1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait_for_pid(left_pid);
	return (wait_for_pid(right_pid));
}
