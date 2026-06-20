#include <fcntl.h>
#include <readline/readline.h>
#include <unistd.h>

#include "executer_internal.h"
#include "validate.h"

static int	apply_heredoc(const char *delimiter, t_shell *shell)
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
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	setup_execution_signals();
	return (pipefd[0]);
}

static int	open_redir_fd(t_redir *redir, t_shell *shell)
{
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == REDIR_OUT)
		return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == APPEND)
		return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (apply_heredoc(redir->file, shell));
}

static int	dup_redir_fd(t_redir *redir, int fd)
{
	if (redir->type == REDIR_IN || redir->type == HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
			return (1);
	}
	else if (dup2(fd, STDOUT_FILENO) < 0)
		return (1);
	return (0);
}

int	apply_redirections(t_node *node, t_shell *shell)
{
	t_redir	*redir;
	int		fd;

	redir = node->redirs;
	while (redir)
	{
		fd = open_redir_fd(redir, shell);
		if (fd < 0)
		{
			if (fd == -2)
				return (-2);
			perror(redir->file);
			return (1);
		}
		if (dup_redir_fd(redir, fd))
		{
			close(fd);
			return (1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}
