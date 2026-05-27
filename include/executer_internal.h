#ifndef EXECUTER_INTERNAL_H
# define EXECUTER_INTERNAL_H

# include <sys/types.h>

# include "executer.h"

char	*resolve_command_path(const char *command, char **envp);
int		apply_redirections(t_node *node);
int		wait_for_pid(pid_t pid);
int		execute_node(t_node *node, t_shell *shell, int in_fd, int out_fd, int fork_command);

#endif