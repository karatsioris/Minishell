#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#include "builtin_internal.h"
#include "libft.h"

static int	echo_skip_flags(t_node *node, int i, int *newline)
{
	int	j;
	int	all_n;

	while (node->args[i] && ft_strncmp(node->args[i], "-n", 2) == 0)
	{
		j = 2;
		all_n = 1;
		while (node->args[i][j])
		{
			if (node->args[i][j] != 'n')
				all_n = 0;
			j++;
		}
		if (!all_n)
			break ;
		*newline = 0;
		i++;
	}
	return (i);
}

static int	builtin_echo(t_node *node)
{
	int	i;
	int	newline;
	int	first;

	newline = 1;
	i = echo_skip_flags(node, 1, &newline);
	first = 1;
	while (node->args[i])
	{
		if (!first)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, node->args[i], ft_strlen(node->args[i]));
		first = 0;
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

static int	builtin_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)))
	{
		write(STDOUT_FILENO, buf, ft_strlen(buf));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	perror("minishell: pwd");
	return (1);
}

static int	builtin_env(t_node *node, t_shell *shell)
{
	int	i;

	if (node->args[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	i = 0;
	while (shell->envp && shell->envp[i])
	{
		write(STDOUT_FILENO, shell->envp[i], ft_strlen(shell->envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}

int	run_builtin_child(t_node *node, t_shell *shell)
{
	if (!node || !node->args || !node->args[0])
		return (-1);
	if (ft_strncmp(node->args[0], "echo", ft_strlen("echo") + 1) == 0)
		return (builtin_echo(node));
	if (ft_strncmp(node->args[0], "pwd", ft_strlen("pwd") + 1) == 0)
		return (builtin_pwd());
	if (ft_strncmp(node->args[0], "env", ft_strlen("env") + 1) == 0)
		return (builtin_env(node, shell));
	if (is_parent_builtin(node->args[0]))
		return (run_builtin_parent(node, shell));
	return (-1);
}
