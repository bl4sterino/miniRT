/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:09:47 by tpotier           #+#    #+#             */
/*   Updated: 2026/02/23 23:46:36 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "rbuf.h"

void	rbuf_init(t_rbuf *self)
{
	*self = (t_rbuf){0};
}

t_io_res	rbuf_new(t_rbuf *self, int fd)
{
	rbuf_init(self);
	self->buf = malloc(DEFAULT_CAPACITY);
	if (!self->buf)
		return (IO_RES_ERR);
	self->cap = DEFAULT_CAPACITY;
	self->fd = fd;
	self->start = 0;
	self->end = 0;
	return (IO_RES_OK);
}
