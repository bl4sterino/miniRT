/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:33:02 by tpotier           #+#    #+#             */
/*   Updated: 2026/02/18 20:19:47 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

t_io_res	rbuf_read_byte(t_rbuf *self, uint8_t *b)
{
	t_io_res	r;

	r = rbuf_peek_byte(self, b);
	if (r != IO_RES_OK)
		return (r);
	rbuf_consume(self, 1);
	return (IO_RES_OK);
}
