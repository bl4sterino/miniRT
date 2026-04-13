# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    module.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/09 22:22:29 by tpotier           #+#    #+#              #
#    Updated: 2026/04/10 17:09:23 by tpotier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBOBJ_NAME ?= libobj.a
LIBOBJ_PREFIX ?= .
LIBOBJ_DEST ?= $(LIBOBJ_PREFIX)/$(LIBOBJ_NAME)

LIBOBJ_INCLUDE_DIR = $(LIBOBJ_PREFIX)/include
LIBOBJ_SRC_DIR = $(LIBOBJ_PREFIX)/src
LIBOBJ_BUILD_DIR = $(LIBOBJ_PREFIX)/build

LIBOBJ_SRCS = iter/iter.c iter/push.c stm/parse.c stm/skip.c stm/parse_v.c stm/parse_vt.c stm/parse_vn.c stm/parse_f.c stm/float.c

LIBOBJ_OBJS = $(addprefix $(LIBOBJ_BUILD_DIR)/,$(LIBOBJ_SRCS:.c=.o))
LIBOBJ_DEPS = $(LIBOBJ_OBJS:.o=.d)

$(LIBOBJ_DEST): $(LIBOBJ_OBJS)
	ar -rcs $@ $^

$(LIBOBJ_BUILD_DIR)/%.o: $(LIBOBJ_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(LIBMEM_PREFIX) -I $(LIBIO_PREFIX) -I $(LIBOBJ_PREFIX) -I $(LIBOBJ_INCLUDE_DIR) -MMD -c $< -o $@

.PHONY: libobj_clean
libobj_clean:
	rm -f $(LIBOBJ_OBJS) $(LIBOBJ_DEPS)

-include $(LIBOBJ_DEPS)
