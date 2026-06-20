/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:18:04 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:18:05 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "executer_internal.h"

static void	free_str_array(char **array)
{
	int	index;

	if (!array)
		return ;
	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

static char	*join_path(const char *prefix, const char *suffix)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(prefix, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, suffix);
	free(tmp);
	return (path);
}

static char	*get_env_value(char **envp, const char *key)
{
	int	index;
	int	key_len;

	if (!envp || !key)
		return (NULL);
	key_len = ft_strlen(key);
	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], key, key_len) == 0
			&& envp[index][key_len] == '=')
			return (envp[index] + key_len + 1);
		index++;
	}
	return (NULL);
}

static char	*search_paths(char **paths, const char *command)
{
	int		index;
	char	*candidate;

	index = 0;
	while (paths[index])
	{
		candidate = join_path(paths[index], command);
		if (candidate && access(candidate, X_OK) == 0)
			return (candidate);
		free(candidate);
		index++;
	}
	return (NULL);
}

char	*resolve_command_path(const char *command, char **envp)
{
	char	**paths;
	char	*path_env;
	char	*found;

	if (!command || command[0] == '\0')
		return (NULL);
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path_env = get_env_value(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	found = search_paths(paths, command);
	free_str_array(paths);
	return (found);
}
