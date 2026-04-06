# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pberne <pberne@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/30 11:15:39 by pberne            #+#    #+#              #
#    Updated: 2026/04/06 20:35:56 by tpotier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g3 -Ofast -Wall -Wextra -Werror
 #DFLAGS = -Ofast -Wall -Wextra -Werror 
DFLAGS = -g3 -Ofast -Wall -Wextra -Werror 
RTFLAGS = -lXext -lX11 -lm
LIBFT_DIR = _libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DEBUG = $(LIBFT_DIR)/libft_DEBUG.a
MLX_DIR = .minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a
NAME = mini-rt
D_NAME = mini-rt_debug
BENCH_NAME = bench_minirt
SRC_DIR = src/
OBJ_DIR = obj/
INCLUDES_DIR =	-Iincludes \
				-Iincludes/collisions \
				-Iincludes/uvs \
				-I$(LIBFT_DIR)/includes \
				-I$(LIBFT_DIR)/includes/vectors \
				-I$(LIBFT_DIR)/includes/inlines \
				-I$(MLX_DIR)

MAIN = main

FILES = main_utils \
		update \
		time \
		image \
		image2 \
		exit \
		exit_2 \
		scene \
		debug/debug_gc \
		input/camera \
		input/focus_and_cursor \
		input/input \
		input/input_get \
		input/key_controls \
		input/key_hook \
		input/object_controls \
		input/object_extra \
		input/object_input \
		input/object_movement \
		input/object_rotation \
		input/object_selection \
		input/render_settings \
		monitoring/clock \
		monitoring/clock_2 \
		parsing/parsing_data_dict \
		parsing/parsing_scene \
		parsing/parsing_scene_processing \
		parsing/parsing_material \
		parsing/parsing_A_C_L \
		parsing/parsing_sp \
		parsing/parsing_pl_cy \
		parsing/parsing_q \
		parsing/parsing_t \
		parsing/parsing_texture \
		parsing/create_hdr_tex \
		parsing/parsing_ellipsoid \
		parsing/parsing_skybox \
		parsing/parsing_scene_builder_A_C_L_sky \
		parsing/parsing_scene_builder_pl_objects \
		parsing/parsing_normalization \
		parsing/parsing_error \
		parsing/parsing_get_bounds \
		parsing/parsing_get_bounds_2 \
		ui/ui_elements \
		ui/hud_display \
		ui/ui_draw_floating \
		rendering/thread_routine \
		rendering/thread_routine_target_caching \
		rendering/render \
		rendering/viewport \
		rendering/bvh_builder \
		rendering/bvh_builder_utils \
		rendering/bvh_utils \
		rendering/bvh_sorter \
		rendering/bvh_ray_debug \
		rendering/bvh_ray \
		rendering/bvh_ray_light \
		rendering/ray_to_color \
		rendering/ray_to_color_utils \
		rendering/shoot_ray_smart \
		rendering/post_processing/post_process \
		rendering/camera/grid \
		utils/camera_vectors_utils \
		utils/data_utils \
		utils/rect

ALL_FILES = $(MAIN) $(FILES)

SRCS = $(addprefix $(SRC_DIR),  $(addsuffix .c, $(ALL_FILES)))

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(ALL_FILES)))
DEP = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(ALL_FILES)))

D_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix _DEBUG.o, $(ALL_FILES)))
D_DEP = $(addprefix $(OBJ_DIR), $(addsuffix _DEBUG.d, $(ALL_FILES)))

DEPFLAGS = -MMD

.PHONY: clean fclean all libft re debug libft-rebuild libft-debug-rebuild bench

all: $(NAME)

debug: $(D_NAME)

ifneq (,$(filter bench,$(MAKECMDGOALS)))
    MAIN = benchmark/main_bvh
    NAME = $(BENCH_NAME)
else
    MAIN = main
endif

bench: $(NAME)

ALL_FILES = $(MAIN) $(FILES)

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
	rm -f $(NAME) $(D_NAME) $(BENCH_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re:
	$(MAKE) fclean
	$(MAKE) all

-include $(DEP) $(D_DEP)
