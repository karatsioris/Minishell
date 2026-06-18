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


// this function evaluate_input() belong to executor so we will remove it later
int	evaluate_input(char	*line, t_shell	*shell)
{
	if (ft_strncmp(line, "exit", 4) == 0)
	{
		shell->running = 0;
		return (shell->exit_code);
	}
	printf("Input: %s\n", line);
	return (0);
}

void	initialization(t_shell	*shell)
{
	shell->exit_code = 0;
	shell->running = 1;
	shell->envp = NULL;
	shell->line = NULL;
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
