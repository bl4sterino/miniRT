/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_triangle.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:36:18 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 17:26:52 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef struct s_triangle_context
{
	t_v3f			edge1;
	t_v3f			edge2;
	t_v3f			h;
	t_v3f			s;
	t_v3f			q;
	float			det;
	float			inv_det;
	float			u;
	float			v;
	float			t;
}					t_triangle_contex;

static inline float	ft_triangle_collision(t_ray ray, t_triangle tri)
{
	t_triangle_contex	c;

	c.edge1 = ft_v3f_sub(tri.points.b, tri.points.a);
	c.edge2 = ft_v3f_sub(tri.points.c, tri.points.a);
	c.h = ft_v3f_cross(ray.direction, c.edge2);
	c.det = ft_v3f_dot(c.edge1, c.h);
	if (c.det > -EPSILON && c.det < EPSILON)
		return (INFINITY);
	c.inv_det = 1.0f / c.det;
	c.s = ft_v3f_sub(ray.origin, tri.points.a);
	c.u = c.inv_det * ft_v3f_dot(c.s, c.h);
	if (c.u < 0.0f || c.u > 1.0f)
		return (INFINITY);
	c.q = ft_v3f_cross(c.s, c.edge1);
	c.v = c.inv_det * ft_v3f_dot(ray.direction, c.q);
	if (c.v < 0.0f || c.u + c.v > 1.0f)
		return (INFINITY);
	c.t = c.inv_det * ft_v3f_dot(c.edge2, c.q);
	if (c.t >= EPSILON)
		return (c.t);
	return (INFINITY);
}
