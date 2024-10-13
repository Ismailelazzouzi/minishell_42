NAME = minishell
HEADER = minishell.h
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
LIBFT = ./libft/libft.a
READLINE_INCLUDE = /Users/isel-azz/.brew/opt/readline/include
READLINE_LIB = /Users/isel-azz/.brew/opt/readline/lib

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
		init_env_var \
		env_handle \
		env_handle1 \
		signal_fun \
		execution \
		builtin_cmd \
		builtin_cmd1 \
		builtin_cmd2 \
		builtin_cmd3 \
		builtins_exec \
		builtins_exec2 \
		cmand_exec_init \
		cmd_exec_control \
		cmd_exec1 \
		heredoc_handl \
		input_cmd_processing \
		path_utils \
		path_utils2 \
		process_pipes_managment \

SRCS = $(addsuffix .c, $(FILES))

OBJS = $(addsuffix .o, $(FILES))


all: $(LIBFT) $(NAME)

$(LIBFT):
	cd ./libft && make

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(READLINE_LIB) -lreadline $(LIBFT) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I$(READLINE_INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJS)
	cd ./libft && make clean

fclean: clean
	$(RM) $(NAME)
	cd ./libft && make fclean

re: fclean all

.PHONY: clean