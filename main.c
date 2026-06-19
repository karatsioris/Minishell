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

int	main(int argc, char **argv, char **envp)
{
	t_shell			shell;
	t_token			*all_token;
	t_node			*ast;
	int				token_count;
    (void)envp;
    (void)argv;
    (void)argc;

	all_token = NULL;
	ast = NULL;
	token_count = 0;

	initialization(&shell);
	while (shell.running)
	{
		if (input_readline(&shell) == NULL)
			break ;
		if (input_handle_error(input_validate(&shell), &shell))
			continue ;
		all_token = array_of_token(&shell, &token_count);
		ast = parse_token(all_token, token_count);
		shell.exit_code = evaluate_input(shell.line, &shell);
		cleanup(&shell, &all_token, token_count, &ast);
	}
	cleanup(&shell, &all_token, token_count, &ast);
	return (shell.exit_code);
}
