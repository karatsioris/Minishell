#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

#include "executer_internal.h"

static int	run_command_node(t_node *node, t_shell *shell)
{
	char	*path;

	if (!node->args || !node->args[0])
	{
		if (apply_redirections(node) != 0)
			return (1);
		return (0);
	}
	if (apply_redirections(node) != 0)
		return (1);
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

	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
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
		pid = fork();
		if (pid == 0)
			_exit(execute_node(node, shell, in_fd, out_fd, 0));
		if (pid < 0)
			return (1);
		return (wait_for_pid(pid));
	}
	status = run_command_node(node, shell);
	return (status);
}