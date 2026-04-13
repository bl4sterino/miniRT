# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    module.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpotier <tpotier@learner.42.tech>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 18:47:44 by tpotier           #+#    #+#              #
#    Updated: 2026/02/18 20:24:12 by tpotier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBIO_NAME ?= libio.a
LIBIO_PREFIX ?= .
LIBIO_DEST ?= $(LIBIO_PREFIX)/$(LIBIO_NAME)

LIBIO_INCLUDE_DIR = $(LIBIO_PREFIX)/include
LIBIO_SRC_DIR = $(LIBIO_PREFIX)/src
LIBIO_BUILD_DIR = $(LIBIO_PREFIX)/build

LIBIO_SRCS = rbuf/new.c rbuf/drop.c rbuf/fill.c rbuf/peek.c rbuf/read.c \
	rbuf/consume.c

LIBIO_OBJS = $(addprefix $(LIBIO_BUILD_DIR)/,$(LIBIO_SRCS:.c=.o))
LIBIO_DEPS = $(LIBIO_OBJS:.o=.d)

$(LIBIO_DEST): $(LIBIO_OBJS)
	ar -rcs $@ $^

$(LIBIO_BUILD_DIR)/%.o: $(LIBIO_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(LIBIO_PREFIX) -I $(LIBIO_INCLUDE_DIR) -MMD -c $< -o $@

.PHONY: libio_clean
libio_clean:
	rm -f $(LIBIO_OBJS) $(LIBIO_DEPS)

-include $(LIBIO_DEPS)
