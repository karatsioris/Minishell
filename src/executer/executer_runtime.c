#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"

#include "executer_internal.h"
#include "builtin.h"

static int	run_command_node(t_node *node, t_shell *shell)
{
	char	*path;
	int		redir_status;

	if (!node->args || !node->args[0])
	{
		redir_status = apply_redirections(node);
		if (redir_status == -2)
			return (130);
		if (redir_status != 0)
			return (1);
		return (0);
	}
	redir_status = apply_redirections(node);
	if (redir_status == -2)
		return (130);
	if (redir_status != 0)
		return (1);
	/* check builtins that can run in child (pwd, env) */
	{
		int builtin_rc = run_builtin_child(node, shell);
		if (builtin_rc != -1)
			return (builtin_rc);
	}
	path = resolve_command_path(node->args[0], shell->envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(node->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (127);
	}
	execve(path, node->args, shell->envp);
	if (errno == EACCES || errno == EISDIR)
		ft_putstr_fd("Permission denied\n", STDERR_FILENO);
	else
		perror(node->args[0]);
	free(path);
	if (errno == EACCES || errno == EISDIR)
		return (126);
	return (127);
}

int	wait_for_pid(pid_t pid)
{
	int	status;

	while (waitpid(pid, &status, 0) < 0)
	{
		if (errno == EINTR)
			continue ;
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "Quit: 3\n", 8);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	execute_node(t_node *node, t_shell *shell, int in_fd, int out_fd, int fork_command)
{
	pid_t	pid;
	int		status;

	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
	{
		int	pipefd[2];
		pid_t	left_pid;
		pid_t	right_pid;
		int		left_status;

		if (pipe(pipefd) < 0)
			return (1);
		left_pid = fork();
		if (left_pid == 0)
		{
			setup_child_signals();
			if (in_fd != STDIN_FILENO)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (pipefd[1] != STDOUT_FILENO)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			close(pipefd[0]);
			status = execute_node(node->left, shell, STDIN_FILENO, STDOUT_FILENO, 0);
			_exit(status);
		}
		if (left_pid < 0)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			return (1);
		}
		right_pid = fork();
		if (right_pid == 0)
		{
			setup_child_signals();
			if (pipefd[0] != STDIN_FILENO)
			{
				dup2(pipefd[0], STDIN_FILENO);
				close(pipefd[0]);
			}
			if (out_fd != STDOUT_FILENO)
			{
				dup2(out_fd, STDOUT_FILENO);
				close(out_fd);
			}
			close(pipefd[1]);
			status = execute_node(node->right, shell, STDIN_FILENO, STDOUT_FILENO, 0);
			_exit(status);
		}
		if (right_pid < 0)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			waitpid(left_pid, NULL, 0);
			return (1);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		left_status = wait_for_pid(left_pid);
		(void)left_status;
		return (wait_for_pid(right_pid));
	}
	if (fork_command)
	{
		/* run parent-only builtins without forking (e.g., cd, exit) */
        
		if (node->args && node->args[0] && is_parent_builtin(node->args[0]))
		{
			int saved_in = dup(STDIN_FILENO);
			int saved_out = dup(STDOUT_FILENO);
			int rc = 0;
			int redir_status;
			redir_status = apply_redirections(node);
			if (redir_status == -2)
			{
				rc = 130;
			}
			else if (redir_status != 0)
			{
				rc = 1;
			}
			else
			{
				rc = run_builtin_parent(node, shell);
				shell->exit_code = rc;
			}
			/* restore fds */
			dup2(saved_in, STDIN_FILENO);
			dup2(saved_out, STDOUT_FILENO);
			close(saved_in);
			close(saved_out);
			return (rc);
		}
		pid = fork();
		if (pid == 0)
		{
			setup_child_signals();
			_exit(execute_node(node, shell, in_fd, out_fd, 0));
		}
		if (pid < 0)
			return (1);
		return (wait_for_pid(pid));
	}
	status = run_command_node(node, shell);
	return (status);
}