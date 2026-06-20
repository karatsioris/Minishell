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
#include <unistd.h>

void	initialization(t_shell	*shell, char **envp)
{
	shell->exit_code = 0;
	shell->running = 1;
	shell->envp = dup_envp(envp);
	shell->line = NULL;
	shell->interactive = isatty(STDIN_FILENO);
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
