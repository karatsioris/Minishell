/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:17:32 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:17:33 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "builtin_internal.h"
#include "libft.h"

static int	export_one_entry(t_shell *shell, char *name, char *equal)
{
	if (!is_valid_identifier(name))
	{
		ft_putstr_fd("minishell: export: not a valid identifier\n",
			STDERR_FILENO);
		return (1);
	}
	if (equal)
		return (set_env_value(shell, name, equal + 1));
	if (env_find_index(shell->envp, name) < 0)
		return (set_env_value(shell, name, ""));
	return (0);
}

int	builtin_export_set(t_node *node, t_shell *shell)
{
	int		i;
	int		status;
	char	*equal;
	char	*name;

	if (!node->args[1])
		return (builtin_export_list(shell));
	status = 0;
	i = 1;
	while (node->args[i])
	{
		equal = ft_strchr(node->args[i], '=');
		if (equal)
			name = ft_substr(node->args[i], 0, equal - node->args[i]);
		else
			name = ft_strdup(node->args[i]);
		status |= export_one_entry(shell, name, equal);
		free(name);
		i++;
	}
	shell->exit_code = status;
	return (status);
}

int	builtin_unset(t_node *node, t_shell *shell)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (node->args[i])
	{
		if (!is_valid_identifier(node->args[i]))
		{
			ft_putstr_fd("minishell: unset: not a valid identifier\n",
				STDERR_FILENO);
			status = 1;
		}
		else
			status |= unset_env_value(shell, node->args[i]);
		i++;
	}
	shell->exit_code = status;
	return (status);
}

int	run_builtin_parent(t_node *node, t_shell *shell)
{
	if (!node || !node->args || !node->args[0])
		return (0);
	if (ft_strncmp(node->args[0], "cd", ft_strlen("cd") + 1) == 0)
		return (builtin_cd(node, shell));
	if (ft_strncmp(node->args[0], "exit", ft_strlen("exit") + 1) == 0)
		return (builtin_exit(node, shell));
	if (ft_strncmp(node->args[0], "export", ft_strlen("export") + 1) == 0)
		return (builtin_export_set(node, shell));
	if (ft_strncmp(node->args[0], "unset", ft_strlen("unset") + 1) == 0)
		return (builtin_unset(node, shell));
	return (0);
}
