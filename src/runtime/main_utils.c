/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 16:40:14 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/18 17:34:36 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "token.h"
#include "parse.h"
#include "builtin.h"
#include "builtin_internal.h"
#include "libft.h"
#include <unistd.h>

static char	*get_env_val(char **envp, const char *name)
{
	int	index;

	index = env_find_index(envp, name);
	if (index < 0)
		return (NULL);
	return (ft_strchr(envp[index], '=') + 1);
}

static void	increment_shlvl(t_shell *shell)
{
	char	*current;
	char	*value;
	int		level;

	current = get_env_val(shell->envp, "SHLVL");
	level = 1;
	if (current)
		level = ft_atoi(current) + 1;
	if (level < 0)
		level = 0;
	value = ft_itoa(level);
	if (!value)
		return ;
	set_env_value(shell, "SHLVL", value);
	free(value);
}

void	initialization(t_shell	*shell, char **envp)
{
	shell->exit_code = 0;
	shell->running = 1;
	shell->envp = dup_envp(envp);
	shell->line = NULL;
	shell->interactive = isatty(STDIN_FILENO);
	if (shell->envp)
		increment_shlvl(shell);
}

void	cleanup(t_shell *shell, t_token	**all_token,
	int token_count, t_node **ast)
{
	free_tokens(*all_token, token_count);
	*all_token = NULL;
	free_ast(*ast);
	*ast = NULL;
	free(shell->line);
	shell->line = NULL;
}
