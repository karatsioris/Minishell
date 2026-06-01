CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I include -I libft
NAME    = minishell

SRCS    =   main.c \
            print_functions.c \
            src/executer/executer.c \
            src/executer/executer_path.c \
            src/executer/executer_redir.c \
            src/executer/executer_runtime.c \
            src/executer/builtin.c \
            src/lexer/lexer.c \
            src/lexer/lexer_free_utils.c \
            src/lexer/lexer_utils.c \
            src/lexer/lexer_quotes.c \
            src/parser/parser.c \
            src/parser/parser_utils.c \
            src/parser/parser_free_utils.c \
            src/validate/validate.c

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