# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melalj <melalj@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 11:00:35 by melalj            #+#    #+#              #
#    Updated: 2020/02/04 23:06:04 by melalj           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = src
SRC_NAME = lem_in_main.c\
			parser.c\
			hash_t.c\
			get_lines.c\
			visu.c\
			tools.c\
			graph_draw.c\
			edges_draw.c\
			graph.c\
			bfs.c\
			queue.c\
			push_ants.c \
			libghiti.c\
			error_exit.c\
			bfs_paths_collector.c

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
LDFLIBS =	-L ~/.brew/Cellar/sdl2/2.0.10/lib -lSDL2-2.0.0 -lSDL2 \
			-L ~/.brew/Cellar/sdl2_image/2.0.5/lib -lSDL2_image \
			-lSDL2_image-2.0.0 \
			-L ~/.brew/Cellar/sdl2_ttf/2.0.15/lib -lSDL2_ttf \
			-lSDL2_ttf-2.0.0 \
			-L libft -lft

CPPFLAGS =	-I ~/.brew/Cellar/sdl2_image/2.0.5/include/SDL2 \
			-I ~/.brew/Cellar/sdl2/2.0.10/include/SDL2 \
			-I ~/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2 \
			-I include \
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