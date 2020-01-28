# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magoumi <magoumi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 11:00:35 by melalj            #+#    #+#              #
#    Updated: 2020/01/22 00:07:10 by magoumi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = src
SRC_NAME = lem_in_main.c\
			parser.c\
			hash_t.c\
			get_lines.c\
			tools.c\
			graph.c\
			bfs.c\
			queue.c\
			push_ants.c
			# edges_draw.c\
			# graph_draw.c\
			# visu.c\

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
LDFLIBS =	-L libft -lft\

CPPFLAGS =	-I include \
			-I libft/include \

CC = gcc
CFLAGS = -Wall -Wextra -g
NAME = lem-in

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	@cd libft ; make
	$(CC) $(LDFLIBS) $^ -o $@ -Llibft -lft -Ilibft

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< -Ilibft

clean:
	@make -C libft clean
	@rm -vf $(OBJ)

#	@rmdir $(OBJ_PATH) 2> /dev/null || true
fclean: clean
	@make -C libft fclean
	@rm -vf $(NAME)
re: fclean all

distcheck:
	uname -a
	$(CC) --version
check:
	@make fclean
	ls -lR
	@make
	./lem-in && echo $?