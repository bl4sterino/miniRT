/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:24:09 by tpotier           #+#    #+#             */
/*   Updated: 2026/02/18 20:19:41 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "rbuf.h"

t_io_res	rbuf_fill(t_rbuf *self)
{
	ssize_t	r;

	if (self->start == self->end)
	{
		r = read(self->fd, self->buf, self->cap);
		if (r < 0)
			return (IO_RES_ERR);
		self->start = 0;
		self->end = r;
		if (self->start == self->end)
			return (IO_RES_EOF);
	}
	return (IO_RES_OK);
}
