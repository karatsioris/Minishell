#ifndef BUILTIN_H
# define BUILTIN_H

# include "parse.h"
# include "shell.h"

int is_parent_builtin(const char *name);
int run_builtin_parent(t_node *node, t_shell *shell);
int run_builtin_child(t_node *node, t_shell *shell);
char **dup_envp(char **envp);
void free_envp(char **envp);

#endif
