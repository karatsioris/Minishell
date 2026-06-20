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

int	main(int argc, char **argv, char **envp)
{
	t_shell			shell;
	t_token			*all_token;
	t_node			*ast;
	int				token_count;

	(void)argv;
	(void)argc;
	all_token = NULL;
	ast = NULL;
	token_count = 0;
	initialization(&shell, envp);
	if (!shell.envp)
	{
		write(STDERR_FILENO, "minishell: failed to copy environment\n", 39);
		return (1);
	}
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	setup_interactive_signals();
	while (shell.running)
	{
		signal_reset();
		if (input_readline(&shell) == NULL)
		{
			if (signal_was_interrupted())
			{
				shell.exit_code = 130;
				signal_reset();
				continue ;
			}
			break ;
		}
		if (input_handle_error(input_validate(&shell), &shell))
			continue ;
		all_token = array_of_token(&shell, &token_count);
		ast = parse_token(all_token, token_count);
		setup_execution_signals();
		shell.exit_code = execute_ast(ast, &shell);
		setup_interactive_signals();
		cleanup(&shell, &all_token, token_count, &ast);
	}
	cleanup(&shell, &all_token, token_count, &ast);
	free_envp(shell.envp);
	return (shell.exit_code);
}
