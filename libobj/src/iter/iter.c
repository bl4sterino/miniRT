/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:02:42 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/10 19:08:42 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

#include "obj.h"
#include "iter.h"
#include "stm.h"

t_io_res	obj_iter_new(t_obj_iter *self, int fd)
{
	self->v_data = NULL;
	self->v_len = 0;
	self->v_cap = 0;
	self->vn_data = NULL;
	self->vn_len = 0;
	self->vn_cap = 0;
	self->vt_data = NULL;
	self->vt_len = 0;
	self->vt_cap = 0;
	return (rbuf_new(&self->rbuf, fd));
}

static t_io_res	make_face(t_obj_iter *self, t_stm_f st, t_obj_f *f)
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		if (st.verts[i].v > self->v_len || st.verts[i].vn > self->vn_len
			|| st.verts[i].vt > self->vt_len)
			return (IO_RES_ERR);
		if (st.verts[i].v > 0)
			f->verts[i].v = self->v_data[st.verts[i].v - 1];
		else
			f->verts[i].v = (t_obj_v){0};
		if (st.verts[i].vn > 0)
			f->verts[i].vn = self->vn_data[st.verts[i].vn - 1];
		else
			f->verts[i].vn = (t_obj_vn){0};
		if (st.verts[i].vt > 0)
			f->verts[i].vt = self->vt_data[st.verts[i].vt - 1];
		else
			f->verts[i].vt = (t_obj_vt){0};
		i++;
	}
	return (IO_RES_OK);
}

t_io_res	obj_iter_next(t_obj_iter *self, t_obj_f *f)
{
	t_io_res	r;
	t_stm		stm;

	while (1)
	{
		r = obj_stm_parse(&stm, &self->rbuf);
		if (r != IO_RES_OK)
			return (r);
		if (stm.ty == STM_V && obj_iter_push_v(self, stm.as.v) != 0)
			return (IO_RES_ERR);
		if (stm.ty == STM_VN && obj_iter_push_vn(self, stm.as.vn) != 0)
			return (IO_RES_ERR);
		if (stm.ty == STM_VT && obj_iter_push_vt(self, stm.as.vt) != 0)
			return (IO_RES_ERR);
		if (stm.ty == STM_F)
			return (make_face(self, stm.as.f, f));
	}
}

void	obj_iter_drop(t_obj_iter *self)
{
	rbuf_drop(&self->rbuf);
	free(self->v_data);
	free(self->vn_data);
	free(self->vt_data);
}
