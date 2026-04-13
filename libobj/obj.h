/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 22:31:14 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/10 17:12:11 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include "io.h"

typedef struct s_obj_v
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_obj_v;

typedef struct s_obj_vn
{
	double	i;
	double	j;
	double	k;
}	t_obj_vn;

typedef struct s_obj_vt
{
	double	u;
	double	v;
	double	w;
}	t_obj_vt;

typedef struct s_obj_vert
{
	t_obj_v		v;
	t_obj_vn	vn;
	t_obj_vt	vt;
}	t_obj_vert;

typedef struct s_obj_f
{
	t_obj_vert	verts[3];
}	t_obj_f;

/*
** Iterates over the faces of a Wavefront Object File (.obj).
*/
typedef struct s_obj_iter
{
	t_obj_v		*v_data;
	size_t		v_len;
	size_t		v_cap;
	t_obj_vn	*vn_data;
	size_t		vn_len;
	size_t		vn_cap;
	t_obj_vt	*vt_data;
	size_t		vt_len;
	size_t		vt_cap;
	t_rbuf		rbuf;
}	t_obj_iter;

t_io_res	obj_iter_new(t_obj_iter *self, int fd);

t_io_res	obj_iter_next(t_obj_iter *self, t_obj_f *f);

void		obj_iter_drop(t_obj_iter *self);

#endif
