/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:17:12 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:17:13 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_internal.h"
#include "libft.h"

static int	append_env_entry(t_shell *shell, char *entry)
{
	int		count;
	char	**new_env;

	count = env_count(shell->envp);
	new_env = env_realloc(shell->envp, count + 1);
	if (!new_env)
	{
		free(entry);
		return (1);
	}
	new_env[count] = entry;
	free(shell->envp);
	shell->envp = new_env;
	return (0);
}

int	set_env_value(t_shell *shell, const char *name, const char *value)
{
	int		index;
	char	*entry;

	if (!shell || !name || !value)
		return (1);
	entry = make_env_entry(name, value);
	if (!entry)
		return (1);
	index = env_find_index(shell->envp, name);
	if (index >= 0)
	{
		free(shell->envp[index]);
		shell->envp[index] = entry;
		return (0);
	}
	return (append_env_entry(shell, entry));
}

static void	shift_env_left(char **new_env, char **envp, int index, int count)
{
	int	i;

	i = 0;
	while (i < index)
	{
		new_env[i] = envp[i];
		i++;
	}
	while (i < count - 1)
	{
		new_env[i] = envp[i + 1];
		i++;
	}
	new_env[count - 1] = NULL;
}

int	unset_env_value(t_shell *shell, const char *name)
{
	int		index;
	int		count;
	char	**new_env;

	if (!shell || !name)
		return (1);
	index = env_find_index(shell->envp, name);
	if (index < 0)
		return (0);
	free(shell->envp[index]);
	count = env_count(shell->envp);
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (1);
	shift_env_left(new_env, shell->envp, index, count);
	free(shell->envp);
	shell->envp = new_env;
	return (0);
}
