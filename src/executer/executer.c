#include "executer_internal.h"

int	execute_ast(t_node *node, t_shell *shell)
{
	if (!shell)
		return (1);
	return (execute_node(node, shell, STDIN_FILENO, STDOUT_FILENO, 1));
}