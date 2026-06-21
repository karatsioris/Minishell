/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:16:40 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:16:44 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "builtin_internal.h"
#include "libft.h"

static void	print_cd_error(const char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd((char *)path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static int	cd_arg_error(t_node *node, t_shell *shell)
{
	if (!node->args[1])
		ft_putstr_fd("minishell: cd: path required\n", STDERR_FILENO);
	else if (node->args[2])
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
	else
		return (0);
	shell->exit_code = 1;
	return (1);
}

static void	update_pwd_env(t_shell *shell, char *oldcwd)
{
	char	newcwd[PATH_MAX];

	if (oldcwd[0])
		set_env_value(shell, "OLDPWD", oldcwd);
	if (getcwd(newcwd, sizeof(newcwd)))
		set_env_value(shell, "PWD", newcwd);
}

int	builtin_cd(t_node *node, t_shell *shell)
{
	char	oldcwd[PATH_MAX];

	if (cd_arg_error(node, shell))
		return (1);
	if (!getcwd(oldcwd, sizeof(oldcwd)))
		oldcwd[0] = '\0';
	if (chdir(node->args[1]) != 0)
	{
		print_cd_error(node->args[1]);
		shell->exit_code = 1;
		return (1);
	}
	update_pwd_env(shell, oldcwd);
	shell->exit_code = 0;
	return (0);
}

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
