#include <unistd.h>

#include "executer_internal.h"
#include "builtin.h"

static int	run_parent_builtin_inline(t_node *node, t_shell *shell)
{
	int	saved_in;
	int	saved_out;
	int	rc;
	int	redir_status;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	rc = 0;
	redir_status = apply_redirections(node, shell);
	if (redir_status == -2)
		rc = 130;
	else if (redir_status != 0)
		rc = 1;
	else
	{
		rc = run_builtin_parent(node, shell);
		shell->exit_code = rc;
	}
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (rc);
}

static int	fork_and_execute(t_node *node, t_shell *shell, t_fds fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		_exit(execute_node(node, shell, fds, 0));
	}
	if (pid < 0)
		return (1);
	return (wait_for_pid(pid));
}

int	execute_node(t_node *node, t_shell *shell, t_fds fds, int fork_command)
{
	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
		return (run_pipe_node(node, shell, fds));
	if (fork_command)
	{
		if (node->args && node->args[0] && is_parent_builtin(node->args[0]))
			return (run_parent_builtin_inline(node, shell));
		return (fork_and_execute(node, shell, fds));
	}
	return (run_command_node(node, shell));
}
