# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpotier <tpotier@learner.42.tech>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 18:32:08 by tpotier           #+#    #+#              #
#    Updated: 2026/03/30 19:34:32 by tpotier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libio.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -O2 -g

.PHONY: all
all: $(NAME)

LIBIO_PREFIX = .
LIBIO_DEST = $(NAME)

-include module.mk

.PHONY: clean
clean: libio_clean

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all
