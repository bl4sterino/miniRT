/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:22:11 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/10 16:22:57 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stm.h"

/* FIXME: handle w */
t_io_res	obj_stm_parse_vt(t_obj_vt *self, t_rbuf *rbuf)
{
	t_io_res	r;

	self->w = 0.0;
	r = obj_skip_ws(rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_parse_float(&self->u, rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_skip_ws(rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	r = obj_parse_float(&self->v, rbuf);
	if (r != IO_RES_OK)
		return (IO_RES_ERR);
	return (IO_RES_OK);
}
