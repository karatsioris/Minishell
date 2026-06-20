/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:17:27 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:17:28 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "builtin_internal.h"
#include "libft.h"

static int	env_entry_cmp(const char *a, const char *b)
{
	while (*a && *a == *b)
	{
		a++;
		b++;
	}
	return ((unsigned char)*a - (unsigned char)*b);
}

static void	sort_env_entries(char **sorted, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (i < count)
	{
		j = i;
		while (j > 0 && env_entry_cmp(sorted[j - 1], sorted[j]) > 0)
		{
			tmp = sorted[j - 1];
			sorted[j - 1] = sorted[j];
			sorted[j] = tmp;
			j--;
		}
		i++;
	}
}

static void	print_export_entry(char *entry)
{
	int	name_len;

	name_len = env_name_len(entry);
	write(STDOUT_FILENO, "declare -x ", 11);
	write(STDOUT_FILENO, entry, name_len);
	if (entry[name_len] == '=')
	{
		write(STDOUT_FILENO, "=\"", 2);
		write(STDOUT_FILENO, entry + name_len + 1,
			ft_strlen(entry + name_len + 1));
		write(STDOUT_FILENO, "\"", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}

int	builtin_export_list(t_shell *shell)
{
	char	**sorted;
	int		count;
	int		i;

	count = env_count(shell->envp);
	sorted = malloc(sizeof(char *) * (count + 1));
	if (!sorted)
		return (1);
	i = 0;
	while (i < count)
	{
		sorted[i] = shell->envp[i];
		i++;
	}
	sorted[count] = NULL;
	sort_env_entries(sorted, count);
	i = 0;
	while (i < count)
	{
		print_export_entry(sorted[i]);
		i++;
	}
	free(sorted);
	return (0);
}
