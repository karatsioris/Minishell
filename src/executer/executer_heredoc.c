/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 10:00:00 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/24 10:00:00 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>

#include "executer_internal.h"
#include "parser_expand.h"
#include "validate.h"

static char	*expand_heredoc_line(const char *line, t_shell *shell)
{
	char	*result;
	char	chunk[2];
	int		i;

	result = ft_strdup("");
	i = 0;
	chunk[1] = '\0';
	while (line && line[i] && result)
	{
		if (line[i] == '$')
			result = expand_dollar(line, &i, shell, result);
		else
		{
			chunk[0] = line[i++];
			result = append_str(result, chunk);
		}
	}
	return (result);
}

static void	write_heredoc_line(int fd, char *line, int expand, t_shell *shell)
{
	char	*out;

	out = line;
	if (expand)
		out = expand_heredoc_line(line, shell);
	if (out)
	{
		write(fd, out, ft_strlen(out));
		write(fd, "\n", 1);
	}
	if (expand && out)
		free(out);
}

int	apply_heredoc(const char *delimiter, int expand, t_shell *shell)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
		return (-1);
	setup_heredoc_signals();
	while (1)
	{
		if (shell->interactive)
			line = readline("> ");
		else
			line = read_noninteractive_line();
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(pipefd[1], line, expand, shell);
		free(line);
	}
	close(pipefd[1]);
	setup_execution_signals();
	return (pipefd[0]);
}
