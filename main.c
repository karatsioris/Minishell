#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <readline/readline.h>
#include <readline/history.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	uc1;
	unsigned char	uc2;

	i = 0;
	while (*s1 != '\0' && *s2 != '\0' && i < n)
	{
		uc1 = (unsigned char)*s1;
		uc2 = (unsigned char)*s2;
		if (uc1 != uc2)
			return (uc1 - uc2);
		s1++;
		s2++;
		i++;
	}
	if (i == n)
		return (0);
	else
		return ((unsigned char)*s1 - (unsigned char)*s2);
}

typedef struct s_shell
{
	int		exit_code;
	int		running;
	char	*line;
	char	**envp;
} t_shell;


int	evaluate_input(char	*line, t_shell	*shell)
{
	if (ft_strncmp(line, "exit", 4) == 0)
	{
		shell->running = 0;
		return (shell->exit_code);
	}

	printf("Input: %s\n", line);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
    t_shell		shell;
    (void)envp;
    (void)argv;
    (void)argc;

	shell.exit_code = 0;
	shell.running = 1;
	shell.envp  = NULL;

    while (shell.running)
    {
        shell.line = readline("minishell$ ");
        if (shell.line == NULL)
		{
			printf("exit\n");
			break;
		}
		if (shell.line[0] != '\0')
			add_history(shell.line);

        shell.exit_code = evaluate_input(shell.line, &shell);
        free(shell.line);
		shell.line = NULL;
    }
    return (shell.exit_code);
}
