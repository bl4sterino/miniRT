/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:03:17 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/10 19:19:05 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stm.h"

t_io_res	obj_skip_to_nl(t_rbuf *rbuf)
{
	t_io_res	r;
	uint8_t		b;

	while (1)
	{
		r = rbuf_peek_byte(rbuf, &b);
		if (r != IO_RES_OK)
			return (r);
		if (b == '\n')
			return (IO_RES_OK);
		rbuf_consume(rbuf, 1);
	}
}

t_io_res	obj_skip_ws(t_rbuf *rbuf)
{
	t_io_res	r;
	uint8_t		b;

	while (1)
	{
		r = rbuf_peek_byte(rbuf, &b);
		if (r != IO_RES_OK)
			return (r);
		if (b != ' ' && b != '\t' && b != '\r')
			return (IO_RES_OK);
		rbuf_consume(rbuf, 1);
	}
}

t_io_res	obj_skip_ws_comment(t_rbuf *rbuf)
{
	t_io_res	r;
	uint8_t		b;

	r = obj_skip_ws(rbuf);
	if (r != IO_RES_OK)
		return (r);
	r = rbuf_peek_byte(rbuf, &b);
	if (r != IO_RES_OK)
		return (r);
	if (b == '#')
		return (obj_skip_to_nl(rbuf));
	return (IO_RES_OK);
}
