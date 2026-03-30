/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_cyl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 12:59:34 by pberne            #+#    #+#             */
/*   Updated: 2026/03/30 11:05:49 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UV_CYL_H
# define UV_CYL_H

# include "rt.h"

typedef struct s_cyl_uv_context
{
	t_v2f			uv;
	t_v3f			cp;
	float			h;
	t_v3f			radial_vec;
	t_v3f			u_axis;
	t_v3f			v_axis;
	float			theta;
}					t_cyl_uv_context;

static inline void	ft_cylinder_body_uv(t_cylinder cyl, t_cyl_uv_context *c)
{
	c->radial_vec = ft_v3f_normalize(ft_v3f_sub(c->cp, ft_v3f_scale(cyl.normal,
					c->h)));
	if (fabsf(cyl.normal.y) < 0.999f)
		c->u_axis = ft_v3f_normalize(ft_v3f_cross(cyl.normal, (t_v3f){{0, 1,
					0}}));
	else
		c->u_axis = ft_v3f_normalize(ft_v3f_cross(cyl.normal, (t_v3f){{0, 0,
					1}}));
	c->v_axis = ft_v3f_cross(cyl.normal, c->u_axis);
	c->theta = atan2f(ft_v3f_dot(c->radial_vec, c->v_axis),
			ft_v3f_dot(c->radial_vec, c->u_axis));
	c->uv.x = 1.0f - (c->theta + M_PI) / (2.0f * M_PI);
	c->uv.y = c->h / cyl.height;
}

static inline t_v2f	ft_cylinder_uv(t_v3f hit_p, t_cylinder cyl)
{
	t_cyl_uv_context	c;

	c.cp = ft_v3f_sub(hit_p, cyl.position);
	c.h = ft_v3f_dot(c.cp, cyl.normal);
	if (c.h < EPSILON || c.h > cyl.height - EPSILON)
	{
		if (fabsf(cyl.normal.y) < 0.999f)
			c.u_axis = ft_v3f_normalize(ft_v3f_cross(cyl.normal, (t_v3f){{0, 1,
						0}}));
		else
			c.u_axis = ft_v3f_normalize(ft_v3f_cross(cyl.normal, (t_v3f){{0, 0,
						1}}));
		c.v_axis = ft_v3f_cross(cyl.normal, c.u_axis);
		c.uv.x = (ft_v3f_dot(c.cp, c.u_axis) / (2.0f * cyl.radius)) + 0.5f;
		c.uv.y = (ft_v3f_dot(c.cp, c.v_axis) / (2.0f * cyl.radius)) + 0.5f;
	}
	else
		ft_cylinder_body_uv(cyl, &c);
	return (c.uv);
}

#endif
