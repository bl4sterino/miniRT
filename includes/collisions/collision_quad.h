/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_quad.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:35:52 by pberne            #+#    #+#             */
/*   Updated: 2026/03/07 16:52:20 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef struct s_quad_collision_context
{
	t_v3f			oc;
	float			denom;
	float			t;
	t_v3f			hit_p;
	t_v3f			planar_pos;
	float			u;
	float			v;
}					t_quad_collision_context;

static inline float	ft_quad_collision(t_ray ray, t_quad quad)
{
	t_quad_collision_context	c;

	c.denom = ft_v3f_dot(quad.normal, ray.direction);
	if (fabsf(c.denom) < EPSILON)
		return (FT_INFINITY);
	c.oc = ft_v3f_sub(quad.position, ray.origin);
	c.t = ft_v3f_dot(c.oc, quad.normal) / c.denom;
	if (c.t < EPSILON)
		return (FT_INFINITY);
	c.hit_p = ft_v3f_add(ray.origin, ft_v3f_scale(ray.direction, c.t));
	c.planar_pos = ft_v3f_sub(c.hit_p, quad.position);
	c.u = ft_v3f_dot(c.planar_pos, quad.u_axis);
	c.v = ft_v3f_dot(c.planar_pos, quad.v_axis);
	if (fabsf(c.u) > quad.size.x * 0.5f || fabsf(c.v) > quad.size.y * 0.5f)
		return (FT_INFINITY);
	return (c.t);
}
