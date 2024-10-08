NAME = minishell
HEADER = minishell.h
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
LIBFT = ./libft/libft.a

FILES = minishell \
		syntax_checker \
		syntax_check_utils \
		tokenize \
		tokenize_utils \
		parse \
		parser_utils \
		utils \
		string_utils \
		string_utils1 \

SRCS = $(addsuffix .c, $(FILES))

OBJS = $(addsuffix .o, $(FILES))


all: $(LIBFT) $(NAME)

$(LIBFT):
	cd ./libft && make

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lreadline $(LIBFT)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	cd ./libft && make clean

fclean: clean
	$(RM) $(NAME)
	cd ./libft && make fclean

re: fclean all

.PHONY: clean