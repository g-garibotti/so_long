# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 11:16:01 by ggaribot          #+#    #+#              #
#    Updated: 2024/09/08 21:49:37 by ggaribot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lXext -lX11 -lm

SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
GAME_DIR = $(SRC_DIR)/game
MAP_DIR = $(SRC_DIR)/map
GRAPHICS_DIR = $(SRC_DIR)/graphics

SRCS = $(CORE_DIR)/main.c \
       $(CORE_DIR)/game_loop.c \
       $(CORE_DIR)/game_exit.c \
       $(MAP_DIR)/map_parser.c \
	   $(MAP_DIR)/map_reader.c \
       $(MAP_DIR)/map_validator.c \
       $(MAP_DIR)/map_solver.c \
       $(GAME_DIR)/player.c \
       $(GRAPHICS_DIR)/render.c \
       $(GRAPHICS_DIR)/textures.c

OBJS_DIR = objs
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

LIBFT = libft/libft.a
MLX = minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -L./minilibx-linux $(MLXFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I./includes -I./libft -I./minilibx-linux -c $< -o $@

$(LIBFT):
	make -C libft

$(MLX):
	make -C minilibx-linux

clean:
	make -C libft clean
	make -C minilibx-linux clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re