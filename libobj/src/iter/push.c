/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:59:30 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/10 19:27:01 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "obj.h"
#include "mem.h"

int	obj_iter_push_v(t_obj_iter *self, t_obj_v v)
{
	size_t	new_cap;
	t_obj_v	*new;

	if (self->v_len >= self->v_cap)
	{
		new_cap = self->v_cap * 2;
		if (new_cap < 16)
			new_cap = 16;
		new = malloc(sizeof(*new) * new_cap);
		if (new == NULL)
			return (-1);
		mem_cpy(new, self->v_data, sizeof(*new) * self->v_len);
		free(self->v_data);
		self->v_data = new;
		self->v_cap = new_cap;
	}
	self->v_data[self->v_len++] = v;
	return (0);
}

int	obj_iter_push_vn(t_obj_iter *self, t_obj_vn vn)
{
	size_t		new_cap;
	t_obj_vn	*new;

	if (self->vn_len >= self->vn_cap)
	{
		new_cap = self->vn_cap * 2;
		if (new_cap < 16)
			new_cap = 16;
		new = malloc(sizeof(*new) * new_cap);
		if (new == NULL)
			return (-1);
		mem_cpy(new, self->vn_data, sizeof(*new) * self->vn_len);
		free(self->vn_data);
		self->vn_data = new;
		self->vn_cap = new_cap;
	}
	self->vn_data[self->vn_len++] = vn;
	return (0);
}

int	obj_iter_push_vt(t_obj_iter *self, t_obj_vt vt)
{
	size_t		new_cap;
	t_obj_vt	*new;

	if (self->vt_len >= self->vt_cap)
	{
		new_cap = self->vt_cap * 2;
		if (new_cap < 16)
			new_cap = 16;
		new = malloc(sizeof(*new) * new_cap);
		if (new == NULL)
			return (-1);
		mem_cpy(new, self->vt_data, sizeof(*new) * self->vt_len);
		free(self->vt_data);
		self->vt_data = new;
		self->vt_cap = new_cap;
	}
	self->vt_data[self->vt_len++] = vt;
	return (0);
}
