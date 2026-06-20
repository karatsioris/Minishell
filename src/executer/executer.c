/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:18:25 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:18:26 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
