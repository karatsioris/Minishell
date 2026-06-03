CC = cc
CFLAGS = -Wall -Wextra -Werror
TARGET = minishell
SRCS = main.c lexer.c lexer_utils.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) libft/libft.a -lreadline

libft/libft.a:
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

re: clean all

clean:
	rm -f $(OBJS) $(TARGET)
	make -C libft clean

.PHONY: all re clean
