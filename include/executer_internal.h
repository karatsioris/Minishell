/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:22:00 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:22:01 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_INTERNAL_H
# define EXECUTER_INTERNAL_H

# include <sys/types.h>

# include "executer.h"
# include "signals.h"

typedef struct s_fds
{
	int	in;
	int	out;
}	t_fds;

char	*resolve_command_path(const char *command, char **envp);
int		apply_heredoc(const char *delimiter, int expand, t_shell *shell);
int		apply_redirections(t_node *node, t_shell *shell);
int		run_command_node(t_node *node, t_shell *shell);
int		run_pipe_node(t_node *node, t_shell *shell, t_fds fds);
int		wait_for_pid(pid_t pid);
int		execute_node(t_node *node, t_shell *shell, t_fds fds, int fork_command);

#endif
