/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_v.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:12:22 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/10 16:21:45 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stm.h"

/* FIXME: handle w */
t_io_res	obj_stm_parse_v(t_obj_v *self, t_rbuf *rbuf)
{
	t_io_res	r;

	self->w = 0.0;
	r = obj_skip_ws(rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_parse_float(&self->x, rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_skip_ws(rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_parse_float(&self->y, rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_skip_ws(rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_parse_float(&self->z, rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	return (IO_RES_OK);
}
