#include <unistd.h>

#include "executer_internal.h"

int	execute_ast(t_node *node, t_shell *shell)
{
	t_fds	fds;

	if (!shell)
		return (1);
	fds.in = STDIN_FILENO;
	fds.out = STDOUT_FILENO;
	return (execute_node(node, shell, fds, 1));
}
