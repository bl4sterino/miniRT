# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pberne <pberne@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/31 16:15:41 by pberne            #+#    #+#              #
#    Updated: 2026/03/03 13:51:34 by pberne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
D_NAME = libft_DEBUG.a

CC = cc
CFLAGS = -Ofast -Wall -Wextra -Werror
SRC_DIR = src/
OBJ_DIR = obj/
INCLUDES_DIR =	includes \
				includes/vectors \
				includes/inlines

FILES =	ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_isspace ft_strhasc \
		ft_strlen ft_nblen ft_strclen ft_toupper ft_tolower ft_strchr ft_strrchr \
		ft_strcapitalize ft_strcapitalize_gc \
		ft_strncmp ft_memchr ft_memcmp ft_strnstr ft_atoi \
		ft_atof \
		ft_atoc \
		ft_atod_safe_restricted \
		ft_has_suffix \
		ft_dtoa ft_dtoa_gc \
		ft_memset ft_bzero ft_memmove ft_strlcpy ft_strlcat \
		ft_strdup \
		ft_calloc ft_calloc_gc \
		ft_memcpy ft_strcmp \
		ft_strjoin \
		ft_strjoin_mult ft_strjoin_strs_gc \
		ft_strtrim \
		ft_str_replace \
		ft_itoa ft_itoa_gc ft_itoa_gc_id \
		ft_substr \
		ft_split ft_split_gc \
		ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd \
		ft_putendl_fd ft_putnbr_fd \
		ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstsort \
		ft_lstadd_back ft_lstdelone ft_lstdelone_fr ft_lstclear ft_lstiter \
		ft_lstmap \
		ft_lst_find \
		get_next_line/get_next_line \
		get_next_line/get_next_line_utils \
		get_next_line/get_next_line_utils2 \
		get_next_line/get_next_line_gc \
		get_next_line/get_next_line_utils_gc \
		get_next_line/get_next_line_utils2_gc \
		ft_free_batch \
		ft_putstr_fd_ret \
		ft_putstr_batch \
		ft_int_comparisons \
		ft_int_min_max \
		ft_sign \
		ft_putstr_fd_count \
		ft_putnbr_base \
		ft_putdouble \
		ft_printf \
		ft_gc ft_gc2 ft_gc2_id \
		ft_swap \
		ft_exit \
		ft_exit_utils \
		dict/dict \
		dict/dict2 \
		parser/parser \
		parser/parser_type \
		utils/ft_malloc_int \
		vectors/v3d_utils \
		ft_read_file_gc \
		ft_writeall

SRCS = $(addprefix $(SRC_DIR),  $(addsuffix .c, $(FILES)))

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))
DEP = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(FILES)))

D_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix _DEBUG.o, $(FILES)))
D_DEP = $(addprefix $(OBJ_DIR), $(addsuffix _DEBUG.d, $(FILES)))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(D_NAME): $(D_OBJ)
	ar rcs $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD $(addprefix -I,$(INCLUDES_DIR)) -c $< -o $@

$(OBJ_DIR)%_DEBUG.o: $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD $(addprefix -I,$(INCLUDES_DIR)) -c $< -o $@

clean:
	rm -f $(OBJ) $(D_OBJ) $(DEP) $(D_DEP)

fclean: clean
	rm -f $(NAME) $(D_NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

debug: CFLAGS += -DDEBUG -g3
debug: $(D_NAME)

.PHONY: all clean fclean re

-include $(DEP) $(D_DEP)
