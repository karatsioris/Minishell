#include <fcntl.h>
#include <readline/readline.h>
#include <unistd.h>

#include "executer_internal.h"

static int	apply_heredoc(const char *delimiter)
{
	int	pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	apply_redirections(t_node *node)
{
	t_redir	*redir;
	int		fd;

	redir = node->redirs;
	while (redir)
	{
		fd = -1;
		if (redir->type == REDIR_IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == HEREDOC)
			fd = apply_heredoc(redir->file);
		if (fd < 0)
		{
			perror(redir->file);
			return (1);
		}
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
		{
			if (dup2(fd, STDIN_FILENO) < 0)
			{
				close(fd);
				return (1);
			}
		}
		else if (dup2(fd, STDOUT_FILENO) < 0)
		{
			close(fd);
			return (1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}