/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:22:23 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:22:25 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	setup_interactive_signals(void);
void	setup_execution_signals(void);
void	setup_heredoc_signals(void);
void	setup_child_signals(void);
int		signal_was_interrupted(void);
void	signal_reset(void);
void	prompt_sigint_handler(int signo);

#endif
