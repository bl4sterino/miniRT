/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 22:51:27 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/10 19:19:25 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STM_H
# define STM_H

# include <stdbool.h>

# include "obj.h"
# include "io.h"

typedef enum e_stmty
{
	STM_V,
	STM_VN,
	STM_VT,
	STM_F,
	STM_UNKNOWN,
}	t_stmty;

/*
** An index of 0 means that the component is not present.
*/
typedef struct s_stm_f_vert
{
	size_t	v;
	size_t	vt;
	size_t	vn;
}	t_stm_f_vert;

/*
** # Warning
**
** Only triangles are currently supported.
*/
typedef struct s_stm_f
{
	t_stm_f_vert	verts[3];
}	t_stm_f;

typedef struct s_stm
{
	t_stmty			ty;
	union u_stm
	{
		t_obj_v		v;
		t_obj_vn	vn;
		t_obj_vt	vt;
		t_stm_f		f;
	}				as;
}	t_stm;

typedef struct s_stm_float
{
	bool		is_neg;
	uint64_t	int_part;
	uint64_t	frac_part;
	size_t		frac_digits;
}	t_stm_float;

t_io_res	obj_stm_parse(t_stm *self, t_rbuf *rbuf);
t_io_res	obj_stm_parse_v(t_obj_v *self, t_rbuf *rbuf);
t_io_res	obj_stm_parse_vn(t_obj_vn *self, t_rbuf *rbuf);
t_io_res	obj_stm_parse_vt(t_obj_vt *self, t_rbuf *rbuf);
t_io_res	obj_stm_parse_f(t_stm_f *self, t_rbuf *rbuf);
t_io_res	obj_parse_float(double *self, t_rbuf *rbuf);
t_io_res	obj_skip_to_nl(t_rbuf *rbuf);
t_io_res	obj_skip_ws(t_rbuf *rbuf);
t_io_res	obj_skip_ws_comment(t_rbuf *rbuf);

#endif
