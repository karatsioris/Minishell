#include <signal.h>
#include <unistd.h>

#include <readline/readline.h>

#include "signals.h"

static volatile sig_atomic_t g_signo = 0;

static void prompt_sigint_handler(int signo)
{
	g_signo = signo;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void set_handler(int signo, void (*handler)(int))
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigaction(signo, &sa, NULL);
}

void setup_interactive_signals(void)
{
	set_handler(SIGINT, prompt_sigint_handler);
	set_handler(SIGQUIT, SIG_IGN);
	g_signo = 0;
}

void setup_execution_signals(void)
{
	set_handler(SIGINT, SIG_IGN);
	set_handler(SIGQUIT, SIG_IGN);
}

void setup_heredoc_signals(void)
{
	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_IGN);
	g_signo = 0;
}

void setup_child_signals(void)
{
	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_DFL);
}

int signal_was_interrupted(void)
{
	return (g_signo != 0);
}

void signal_reset(void)
{
	g_signo = 0;
}