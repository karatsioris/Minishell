/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:18:37 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:18:38 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
