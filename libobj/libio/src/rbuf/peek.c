/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peek.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:18:39 by tpotier           #+#    #+#             */
/*   Updated: 2026/02/18 20:19:52 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbuf.h"

t_io_res	rbuf_peek_byte(t_rbuf *self, uint8_t *b)
{
	t_io_res	r;

	r = rbuf_fill(self);
	if (r != IO_RES_OK)
		return (r);
	*b = self->buf[self->start];
	return (IO_RES_OK);
}
