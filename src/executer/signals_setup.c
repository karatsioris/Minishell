#include <signal.h>
#include <stddef.h>

#include "signals.h"

static void	set_handler(int signo, void (*handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigaction(signo, &sa, NULL);
}

void	setup_interactive_signals(void)
{
	set_handler(SIGINT, prompt_sigint_handler);
	set_handler(SIGQUIT, SIG_IGN);
	signal_reset();
}

void	setup_execution_signals(void)
{
	set_handler(SIGINT, SIG_IGN);
	set_handler(SIGQUIT, SIG_IGN);
}

void	setup_heredoc_signals(void)
{
	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_IGN);
	signal_reset();
}

void	setup_child_signals(void)
{
	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_DFL);
}
