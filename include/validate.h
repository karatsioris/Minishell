/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:43:02 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/18 16:23:20 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_H
# define VALIDATE_H

# include "shell.h"
# include "stdlib.h"

typedef enum e_syntax_error
{
	SYNTAX_OK,
	SYNTAX_UNCLOSED_SINGLE_QUOTE,
	SYNTAX_UNCLOSED_DOUBLE_QUOTE,
	SYNTAX_PIPE_AT_START,
	SYNTAX_PIPE_AT_END,
	SYNTAX_DOUBLE_PIPE,
	SYNTAX_INVALID_OPERATOR,
}	t_syntax_error;

// validate.c
t_syntax_error	input_validate(t_shell	*shell);
const char		*input_readline(t_shell	*shell);
int				input_handle_error(t_syntax_error	err, t_shell *shell);
char			*read_noninteractive_line(void);

// validate_utils.c
int				skip_spaces(const char *input, int i);
t_syntax_error	check_pipes(const char *input);
t_syntax_error	check_after_operator(const char *input, int i);
t_syntax_error	check_redirections(const char *input);
t_syntax_error	check_quotes(const char *input);


#endif