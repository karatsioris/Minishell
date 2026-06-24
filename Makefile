CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I include -I libft
NAME    = minishell

SRCS    =   main.c \
            src/runtime/main_utils.c \
            src/executer/executer.c \
            src/executer/executer_path.c \
            src/executer/executer_redir.c \
            src/executer/executer_heredoc.c \
            src/executer/executer_exec.c \
            src/executer/executer_pipe.c \
            src/executer/executer_dispatch.c \
            src/executer/signals_setup.c \
            src/executer/signals_state.c \
            src/executer/builtin_env_utils.c \
            src/executer/builtin_env_set.c \
            src/executer/builtin_env_dup.c \
            src/executer/builtin_validators.c \
            src/executer/builtin_cd.c \
            src/executer/builtin_exit.c \
            src/executer/builtin_export_print.c \
            src/executer/builtin_export_unset.c \
            src/executer/builtin_child.c \
            src/lexer/lexer.c \
            src/lexer/lexer_free_utils.c \
            src/lexer/lexer_utils.c \
            src/lexer/lexer_quotes.c \
            src/parser/parser.c \
            src/parser/parser_utils.c \
            src/parser/parser_free_utils.c \
            src/parser/parser_cmd.c \
            src/parser/parser_expand.c \
            src/parser/parser_expand_var.c \
            src/validate/validate.c \
            src/validate/validate_utils.c \
            src/validate/validate_pipe.c \
            src/validate/validate_redir.c

OBJS    = $(SRCS:.c=.o)
all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a -lreadline

libft/libft.a:
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(CFLAGS) -I include -c $< -o $@

re: fclean all

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)

.PHONY: all re clean fclean