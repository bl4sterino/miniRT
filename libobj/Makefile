# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/09 22:30:17 by tpotier           #+#    #+#              #
#    Updated: 2026/04/10 17:22:56 by tpotier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libobj.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -O2 -g

.PHONY: all
all: $(NAME)

LIBIO_PREFIX = libio

LIBMEM_PREFIX = libmem

LIBOBJ_PREFIX = .
LIBOBJ_DEST = $(NAME)

-include $(LIBOBJ_PREFIX)/module.mk

.PHONY: clean
clean: libobj_clean

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all
