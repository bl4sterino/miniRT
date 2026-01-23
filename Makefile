# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pberne <pberne@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/30 11:15:39 by pberne            #+#    #+#              #
#    Updated: 2026/01/23 11:36:49 by pberne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -O3 -Wall -Wextra -Werror
DFLAGS = -g3 -DDEBUG=1 -Wall -Wextra #-Werror
MLXFLAG = -lXext -lX11 -lm
LIBFT_DIR = _libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DEBUG = $(LIBFT_DIR)/libft_DEBUG.a
MLX_DIR = .minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a

NAME = raytracer
D_NAME = raytracer_debug

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDES_DIR =	-Iincludes\
				-I$(LIBFT_DIR)/includes\
				-I$(LIBFT_DIR)/includes/vectors\
				-I$(LIBFT_DIR)/includes/inlines\
				-I$(MLX_DIR) 

FILES = main\
		update\
		time\
		image\
		image2\
		exit\
		debug/debug_gc\
		input/focus_and_cursor\
		input/input\
		input/input_get\
		input/key_controls\
		input/key_hook\
		monitoring/clock\
		monitoring/clock_2\
		parsing/parsing_data_dict\
		parsing/parsing_scene\
		parsing/parsing_A_C_L\
		parsing/parsing_sp_pl_cy\
		parsing/parsing_scene_builder_A_C_L\
		parsing/parsing_scene_builder_sp_pl_cy\
		parsing/parsing_normalization\
		parsing/parsing_error\
		ui/ui_elements\
		ui/hud_display\
		rendering/basic_rt\
		rendering/render\
		rendering/viewport\
		collisions/sphere_collision\
		utils/camera_vectors_utils\
		camera


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
	make -C $(MLX_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | obj
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES_DIR) -c $< -o $@

$(OBJ_DIR)%_DEBUG.o: $(SRC_DIR)%.c | obj
	$(CC) $(DFLAGS) $(DEPFLAGS) $(INCLUDES_DIR) -c $< -o $@


$(LIBFT): libft-rebuild
	@true

libft-rebuild:
	make -C $(LIBFT_DIR) all

$(LIBFT_DEBUG): libft-debug-rebuild
	@true

libft-debug-rebuild:
	make -C $(LIBFT_DIR) debug


obj:
	mkdir -p $@

clean:
	rm -f $(OBJ) $(D_OBJ) $(DEP) $(D_DEP)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(D_NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

re: fclean all

-include $(DEP) $(D_DEP)