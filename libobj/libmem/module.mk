# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    module.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/30 19:10:51 by tpotier           #+#    #+#              #
#    Updated: 2026/03/31 15:52:15 by tpotier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBMEM_NAME ?= libmem.a
LIBMEM_PREFIX ?= .
LIBMEM_DEST ?= $(LIBMEM_PREFIX)/$(LIBMEM_NAME)

LIBMEM_INCLUDE_DIR = $(LIBMEM_PREFIX)/include
LIBMEM_SRC_DIR = $(LIBMEM_PREFIX)/src
LIBMEM_BUILD_DIR = $(LIBMEM_PREFIX)/build

LIBMEM_SRCS = cpy.c strlen.c

LIBMEM_OBJS = $(addprefix $(LIBMEM_BUILD_DIR)/,$(LIBMEM_SRCS:.c=.o))
LIBMEM_DEPS = $(LIBMEM_OBJS:.o=.d)

$(LIBMEM_DEST): $(LIBMEM_OBJS)
	ar -rcs $@ $^

$(LIBMEM_BUILD_DIR)/%.o: $(LIBMEM_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(LIBMEM_PREFIX) -I $(LIBMEM_INCLUDE_DIR) -MMD -c $< -o $@

.PHONY: libmem_clean
libmem_clean:
	rm -f $(LIBMEM_OBJS) $(LIBMEM_DEPS)

-include $(LIBMEM_DEPS)
