# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/30 19:13:21 by tpotier           #+#    #+#              #
#    Updated: 2026/03/30 19:56:22 by tpotier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmem.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -O2 -g

.PHONY: all
all: $(NAME)

LIBMEM_PREFIX = .
LIBMEM_DEST = $(NAME)

-include module.mk

.PHONY: clean
clean: libmem_clean

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all
