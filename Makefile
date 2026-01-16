# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pberne <pberne@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/30 11:15:39 by pberne            #+#    #+#              #
#    Updated: 2026/01/16 14:29:35 by pberne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -O3 -Wall -Wextra -Werror
DFLAGS = -O3 -g3 -Wall -Wextra #-Werror
MLXFLAG = -lXext -lX11 -lm
LIBFT = libft/libft.a
LIBFT_DEBUG = libft/libft_DEBUG.a
MLX = minilibx-linux/libmlx_Linux.a

NAME = raytracer
D_NAME = raytracer_debug

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDES_DIR = -Iincludes -Ilibft/includes -Iminilibx-linux

FILES = main\
		update\
		time\
		image\
		image2\
		exit\
		input/focus_and_cursor\
		input/input\
		input/input_get\
		input/key_controls\
		input/key_hook\
		camera\
		ui

SRCS = $(addprefix $(SRC_DIR),  $(addsuffix .c, $(FILES)))

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))
DEP = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(FILES)))

D_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix _DEBUG.o, $(FILES)))
D_DEP = $(addprefix $(OBJ_DIR), $(addsuffix _DEBUG.d, $(FILES)))

DEPFLAGS = -MMD

.PHONY: clean fclean all libft re debug libft-rebuild libft-debug-rebuild

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME) $(MLXFLAG)

$(D_NAME): $(LIBFT_DEBUG) $(MLX) $(D_OBJ)
	$(CC) $(DFLAGS) $(D_OBJ) $(LIBFT_DEBUG) $(MLX) -o $(D_NAME) $(MLXFLAG)

debug: $(D_NAME)


$(MLX):
	make -C minilibx-linux

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | obj
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES_DIR) -c $< -o $@

$(OBJ_DIR)%_DEBUG.o: $(SRC_DIR)%.c | obj
	$(CC) $(DFLAGS) $(DEPFLAGS) $(INCLUDES_DIR) -c $< -o $@


$(LIBFT): libft-rebuild
	@true

libft-rebuild:
	make -C libft all

$(LIBFT_DEBUG): libft-debug-rebuild
	@true

libft-debug-rebuild:
	make -C libft debug


obj:
	mkdir -p $@

clean:
	rm -f $(OBJ) $(D_OBJ) $(DEP) $(D_DEP)
	make -C libft clean
	make -C minilibx-linux clean

fclean: clean
	rm -f $(NAME) $(D_NAME)
	make -C libft fclean
	make -C minilibx-linux clean

re: fclean all

-include $(DEP) $(D_DEP)