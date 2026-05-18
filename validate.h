#ifndef VALIDATE_H

typedef enum e_syntax_error
{
    SYNTAX_OK,
    SYNTAX_UNCLOSED_SINGLE_QUOTE,
    SYNTAX_UNCLOSED_DOUBLE_QUOTE,
    SYNTAX_PIPE_AT_START,
    SYNTAX_PIPE_AT_END,
    SYNTAX_DOUBLE_PIPE,
    SYNTAX_INVALID_OPERATOR,
} t_syntax_error;


t_syntax_error  validate_input(const char *input);

int				skip_spaces(const char *input, int i);
t_syntax_error	check_pipes(const char *input);
t_syntax_error  check_after_operator(const char *input, int i);
t_syntax_error	check_redirections(const char *input);
t_syntax_error	check_quotes(const char *input);



#endif