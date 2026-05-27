#ifndef EXECUTER_H
# define EXECUTER_H

# include "parse.h"

int		execute_ast(t_node *node, t_shell *shell);
void	free_tokens(t_token *tokens, int count);
void	free_ast(t_node *node);

#endif