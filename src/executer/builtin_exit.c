/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 15:00:00 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/21 16:14:35 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "builtin_internal.h"
#include "libft.h"

int	builtin_exit(t_node *node, t_shell *shell)
{
	if (node->args[1] && !is_valid_exit_arg(node->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(node->args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		shell->exit_code = 2;
		shell->running = 0;
		return (shell->exit_code);
	}
	if (node->args[1] && node->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		shell->exit_code = 1;
		return (1);
	}
	if (node->args[1])
		shell->exit_code = ft_atoi(node->args[1]);
	shell->running = 0;
	return (shell->exit_code);
}
