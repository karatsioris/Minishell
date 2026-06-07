#ifndef SIGNALS_H
# define SIGNALS_H

void setup_interactive_signals(void);
void setup_execution_signals(void);
void setup_heredoc_signals(void);
void setup_child_signals(void);
int signal_was_interrupted(void);
void signal_reset(void);

#endif