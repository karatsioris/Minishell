#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>

#include "signals.h"

static volatile sig_atomic_t	g_signo = 0;

void	prompt_sigint_handler(int signo)
{
	g_signo = signo;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	signal_was_interrupted(void)
{
	return (g_signo != 0);
}

void	signal_reset(void)
{
	g_signo = 0;
}
