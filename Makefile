# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/04 14:36:49 by mlazzare          #+#    #+#              #
#    Updated: 2021/08/31 21:48:02 by mlazzare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -g3
CFLAGS = -Wall -Wextra -Werror
#CFAGS += -fsanitize=address

# sudo apt-get install libreadline-dev <-- handle installation for linux

OS = $(shell uname -s)

ifeq ($(OS), Linux)
	LIB = -L/usr/include -I/usr/local/include -lreadline -L./libft -lft
else
	LIB = -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include -lreadline -L./libft -lft	
endif

HEADER = -I./inc \

SRC = \
		./src/parser/init_shell.c \
		./src/parser/parse_shell.c \
		./src/parser/parse_arg.c \
		./src/exec/exec_shell.c \
		./src/exec/pipe_process.c \
		./src/exec/file_redir.c \
		./src/exec/here_doc.c \
		./src/exec/cd.c \
		./src/env/var.c \
		./src/env/enver.c \
		./src/utils/free.c \
		./src/utils/reset.c \
		./src/utils/error_msg.c \
		./src/utils/comp.c \
		./src/main.c \

OBJ = $(SRC:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) $(LIB) $< -o $@

LIBFT = ./libft/libft.a

$(NAME): $(LIBFT) $(SRC)
		$(CC) $(SRC) $(CFLAGS) $(LIB) $(HEADER) -o $(NAME)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

clean:
		rm -rf $(OBJ)
		@cd libft && make clean

fclean: clean
		rm -rf $(NAME)
		@cd libft && make fclean

re:	fclean all

.PHONY: all clean fclean re
