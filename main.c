/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:38:58 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/18 17:34:16 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validate.h"
#include "runtime.h"
#include "executer.h"
#include "builtin.h"
#include "signals.h"
#include <readline/readline.h>

static int	init_shell(t_shell *shell, char **envp)
{
	initialization(shell, envp);
	if (!shell->envp)
	{
		write(STDERR_FILENO, "minishell: failed to copy environment\n", 39);
		return (0);
	}
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	setup_interactive_signals();
	return (1);
}

static int	read_and_validate(t_shell *shell)
{
	if (input_readline(shell) == NULL)
	{
		if (signal_was_interrupted())
		{
			shell->exit_code = 130;
			signal_reset();
			return (1);
		}
		return (-1);
	}
	if (input_handle_error(input_validate(shell), shell))
		return (1);
	return (0);
}

static void	run_line(t_shell *shell, t_token **all_token, t_node **ast,
		int *token_count)
{
	*all_token = array_of_token(shell, token_count);
	*ast = parse_token(*all_token, *token_count);
	setup_execution_signals();
	shell->exit_code = execute_ast(*ast, shell);
	setup_interactive_signals();
	cleanup(shell, all_token, *token_count, ast);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_token	*all_token;
	t_node	*ast;
	int		token_count;
	int		status;

	(void)argv;
	(void)argc;
	all_token = NULL;
	ast = NULL;
	token_count = 0;
	if (!init_shell(&shell, envp))
		return (1);
	while (shell.running)
	{
		signal_reset();
		status = read_and_validate(&shell);
		if (status == -1)
			break ;
		if (status == 1)
			continue ;
		run_line(&shell, &all_token, &ast, &token_count);
	}
	free_envp(shell.envp);
	return (shell.exit_code);
}
