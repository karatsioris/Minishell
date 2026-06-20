/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:17:03 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:17:08 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_internal.h"
#include "libft.h"

char	**dup_envp(char **envp)
{
	char	**dup;
	int		count;
	int		i;

	count = env_count(envp);
	dup = malloc(sizeof(char *) * (count + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup[i] = ft_strdup(envp[i]);
		if (!dup[i])
		{
			while (i > 0)
				free(dup[--i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[count] = NULL;
	return (dup);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
