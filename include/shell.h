#ifndef SHELL_H
# define SHELL_H

typedef struct s_shell
{
	int		exit_code;
	int		running;
	char	*line;
	char	**envp;
}	t_shell;

#endif