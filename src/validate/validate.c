/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:39:30 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/18 16:33:37 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validate.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

static char	*append_char(char *line, char c)
{
	char	suffix[2];
	char	*joined;

	suffix[0] = c;
	suffix[1] = '\0';
	joined = ft_strjoin(line, suffix);
	free(line);
	return (joined);
}

char	*read_noninteractive_line(void)
{
	char	*line;
	char	buf[1];
	ssize_t	got_any;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	got_any = read(STDIN_FILENO, buf, 1);
	while (got_any > 0 && buf[0] != '\n')
	{
		line = append_char(line, buf[0]);
		if (!line)
			return (NULL);
		got_any = read(STDIN_FILENO, buf, 1);
	}
	if (got_any <= 0 && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static const char *g_syntax_errors[] = {
[SYNTAX_OK] = NULL,
[SYNTAX_UNCLOSED_SINGLE_QUOTE] = "syntax error: unclosed single quote",
[SYNTAX_UNCLOSED_DOUBLE_QUOTE] = "syntax error: unclosed double quote",
[SYNTAX_PIPE_AT_START] = "syntax error near unexpected token `|'",
[SYNTAX_PIPE_AT_END] = "syntax error near unexpected token `|'",
[SYNTAX_DOUBLE_PIPE] = "syntax error near unexpected token `||'",
[SYNTAX_INVALID_OPERATOR] = "syntax error near unexpected token",
};

t_syntax_error	input_validate(t_shell	*shell)
{
	t_syntax_error	err;

	if (shell->line == NULL)
		return (SYNTAX_OK);

	err = check_pipes(shell->line);
	if (err != SYNTAX_OK)
		return (err);
	err = check_redirections(shell->line);
	if (err != SYNTAX_OK)
		return (err);
	err = check_quotes(shell->line);
	if (err != SYNTAX_OK)
		return (err);

	return (SYNTAX_OK);
}

const char	*input_readline(t_shell	*shell)
{
	if (shell->interactive)
		shell->line = readline("minishell$ ");
	else
		shell->line = read_noninteractive_line();
	if (shell->line == NULL)
		return (NULL);
	if (shell->interactive && shell->line[0] != '\0')
		add_history(shell->line);
	return (shell->line);
}

int	input_handle_error(t_syntax_error	err, t_shell *shell)
{
	if (err != SYNTAX_OK)
	{
		printf("minishell: %s\n", g_syntax_errors[err]);
		shell->exit_code = 258;
		free(shell->line);
		shell->line = NULL;
		return (1);
	}
	return (0);
}