/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:30:44 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/10 22:27:11 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stm.h"

static t_io_res	parse_size_t(size_t *self, t_rbuf *rbuf)
{
	t_io_res	r;
	uint8_t		b;

	*self = 0;
	while (1)
	{
		r = rbuf_peek_byte(rbuf, &b);
		if (r != IO_RES_OK)
			return (r);
		if (!('0' <= b && b <= '9'))
			break ;
		*self = *self * 10 + b - '0';
		rbuf_consume(rbuf, 1);
	}
	return (IO_RES_OK);
}

static t_io_res	parse_size_and_slash(size_t *self, t_rbuf *rbuf, bool *done)
{
	t_io_res	r;
	uint8_t		b;

	r = parse_size_t(self, rbuf);
	if (r != IO_RES_OK)
		return (r);
	r = rbuf_peek_byte(rbuf, &b);
	if (r != IO_RES_OK)
		return (r);
	*done = b != '/';
	if (*done)
		return (IO_RES_OK);
	rbuf_consume(rbuf, 1);
	return (IO_RES_OK);
}

static t_io_res	parse_vert(t_stm_f_vert *self, t_rbuf *rbuf)
{
	t_io_res	r;
	bool		done;

	self->v = 0;
	self->vt = 0;
	self->vn = 0;
	r = parse_size_and_slash(&self->v, rbuf, &done);
	if (r != IO_RES_OK)
		return (r);
	if (done)
		return (IO_RES_OK);
	r = parse_size_and_slash(&self->vt, rbuf, &done);
	if (r != IO_RES_OK)
		return (r);
	if (done)
		return (IO_RES_OK);
	return (parse_size_t(&self->vn, rbuf));
}

t_io_res	obj_stm_parse_f(t_stm_f *self, t_rbuf *rbuf)
{
	t_io_res	r;

	r = obj_skip_ws(rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = parse_vert(&self->verts[0], rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_skip_ws(rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = parse_vert(&self->verts[1], rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_skip_ws(rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = parse_vert(&self->verts[2], rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	return (IO_RES_OK);
}
