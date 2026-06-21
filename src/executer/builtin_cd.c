/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:16:40 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/21 15:00:00 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "builtin_internal.h"
#include "libft.h"

static void	cd_error(const char *path, const char *msg)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (path)
	{
		ft_putstr_fd((char *)path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd((char *)msg, STDERR_FILENO);
}

static char	*target_from_env(t_shell *shell, const char *name)
{
	int	index;

	index = env_find_index(shell->envp, name);
	if (index >= 0)
		return (ft_strchr(shell->envp[index], '=') + 1);
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd((char *)name, STDERR_FILENO);
	ft_putendl_fd(" not set", STDERR_FILENO);
	return (NULL);
}

static char	*resolve_cd_target(t_node *node, t_shell *shell)
{
	if (node->args[1] && node->args[2])
	{
		cd_error(NULL, "too many arguments");
		return (NULL);
	}
	if (!node->args[1])
		return (target_from_env(shell, "HOME"));
	if (ft_strncmp(node->args[1], "-", 2) == 0)
		return (target_from_env(shell, "OLDPWD"));
	return (node->args[1]);
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
	char	*target;

	target = resolve_cd_target(node, shell);
	if (!target)
		return (shell->exit_code = 1, 1);
	if (!getcwd(oldcwd, sizeof(oldcwd)))
		oldcwd[0] = '\0';
	if (chdir(target) != 0)
	{
		cd_error(target, strerror(errno));
		return (shell->exit_code = 1, 1);
	}
	if (node->args[1] && ft_strncmp(node->args[1], "-", 2) == 0)
		ft_putendl_fd(target, STDOUT_FILENO);
	update_pwd_env(shell, oldcwd);
	shell->exit_code = 0;
	return (0);
}
