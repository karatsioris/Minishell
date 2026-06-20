#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

#include "executer_internal.h"
#include "builtin.h"

static void	report_exec_error(char *path, char *cmd)
{
	struct stat	st;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	else if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
}

static int	run_external_command(t_node *node, t_shell *shell)
{
	char	*path;

	path = resolve_command_path(node->args[0], shell->envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(node->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (127);
	}
	execve(path, node->args, shell->envp);
	report_exec_error(path, node->args[0]);
	free(path);
	if (errno == EACCES || errno == EISDIR)
		return (126);
	return (127);
}

int	run_command_node(t_node *node, t_shell *shell)
{
	int	redir_status;
	int	builtin_rc;

	redir_status = apply_redirections(node, shell);
	if (redir_status == -2)
		return (130);
	if (redir_status != 0)
		return (1);
	if (!node->args || !node->args[0])
		return (0);
	builtin_rc = run_builtin_child(node, shell);
	if (builtin_rc != -1)
		return (builtin_rc);
	return (run_external_command(node, shell));
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
