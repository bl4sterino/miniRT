# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pberne <pberne@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/30 11:15:39 by pberne            #+#    #+#              #
#    Updated: 2026/03/04 14:09:28 by pberne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -O3 -Wall -Wextra -Werror
DFLAGS = -O3 -march=native -g3 -Wall -Wextra #-Werror
RTFLAGS = -lXext -lX11 -lm
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
				-Iincludes/collisions\
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
		exit_2\
		debug/debug_gc\
		input/camera\
		input/focus_and_cursor\
		input/input\
		input/input_listeners\
		input/input_get\
		input/key_controls\
		input/key_hook\
		input/object_controls\
		input/object_extra\
		input/object_input\
		input/object_movement\
		input/object_rotation\
		input/object_selection\
		input/render_settings\
		monitoring/clock\
		monitoring/clock_2\
		parsing/parsing_data_dict\
		parsing/parsing_scene\
		parsing/parsing_material\
		parsing/parsing_A_C_L\
		parsing/parsing_sp\
		parsing/parsing_pl_cy\
		parsing/parsing_q\
		parsing/parsing_t\
		parsing/parsing_scene_builder_A_C_L\
		parsing/parsing_scene_builder_pl_objects\
		parsing/parsing_normalization\
		parsing/parsing_error\
		parsing/parsing_get_bounds\
		ui/ui_elements\
		ui/hud_display\
		rendering/thread_routine\
		rendering/render\
		rendering/viewport\
		rendering/bvh_builder\
		rendering/bvh_utils\
		rendering/bvh_sorter\
		rendering/bvh_ray_debug\
		rendering/bvh_ray\
		rendering/bvh_ray_light\
		rendering/task_builder\
		rendering/ray_to_color\
		rendering/post_processing/post_process\
		utils/camera_vectors_utils


SRCS = $(addprefix $(SRC_DIR),  $(addsuffix .c, $(FILES)))

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))
DEP = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(FILES)))

D_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix _DEBUG.o, $(FILES)))
D_DEP = $(addprefix $(OBJ_DIR), $(addsuffix _DEBUG.d, $(FILES)))

DEPFLAGS = -MMD

.PHONY: clean fclean all libft re debug libft-rebuild libft-debug-rebuild opencl opencl_debug

all: $(NAME)

debug: $(D_NAME)


$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME) $(RTFLAGS)

$(D_NAME): $(LIBFT_DEBUG) $(MLX) $(D_OBJ)
	$(CC) $(DFLAGS) $(D_OBJ) $(LIBFT_DEBUG) $(MLX) -o $(D_NAME) $(RTFLAGS)
	

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | obj
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES_DIR) -c $< -o $@

$(OBJ_DIR)%_DEBUG.o: $(SRC_DIR)%.c | obj
	mkdir -p $(dir $@)
	$(CC) $(DFLAGS) $(DEPFLAGS) $(INCLUDES_DIR) -c $< -o $@


$(LIBFT): libft-rebuild
	@true

libft-rebuild:
	$(MAKE) -C $(LIBFT_DIR) all

$(LIBFT_DEBUG): libft-debug-rebuild
	@true

libft-debug-rebuild:
	$(MAKE) -C $(LIBFT_DIR) debug


obj:
	mkdir -p $@

clean:
	rm -f $(OBJ) $(D_OBJ) $(DEP) $(D_DEP)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(D_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

-include $(DEP) $(D_DEP)