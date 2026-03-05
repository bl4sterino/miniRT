/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_points_inlined.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:56:11 by pberne            #+#    #+#             */
/*   Updated: 2026/03/05 16:47:57 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SURFACE_POINTS_INLINED_H
# define SURFACE_POINTS_INLINED_H

# include "rt.h"

static inline t_v3f	ft_random_point_sphere(t_sphere sp)
{
	t_v3f	rand_dir;

	rand_dir = ft_v3f_normalize(ft_v3f_random());
	return (ft_v3f_add(sp.position, ft_v3f_scale(rand_dir, sp.radius - EPSILON
				* 2.0f)));
}

static inline t_v3f	ft_random_point_quad(t_quad q)
{
	t_v3f	ret;
	t_v3f	u_rand;
	t_v3f	v_rand;

	ret = q.position;
	u_rand = ft_v3f_scale(q.u_axis, (q.size.x * (0.5f - EPSILON)) * (fast_rand()
				* 2.0f - 1.0f));
	v_rand = ft_v3f_scale(q.v_axis, (q.size.y * (0.5f - EPSILON)) * (fast_rand()
				* 2.0f - 1.0f));
	return ((t_v3f){{ret.x + u_rand.x + v_rand.x, ret.y + u_rand.y + v_rand.y,
			ret.z + u_rand.z + v_rand.z}});
}

static inline t_v3f	ft_random_point_triangle(t_triangle tri)
{
	t_v3f	p;

	p = ft_v3f_lerp(tri.points.a, tri.points.b, fast_rand());
	return (ft_v3f_lerp(p, tri.points.c, fast_rand()));
}

static inline t_v3f	ft_get_random_point_on_object(t_object object)
{
	if (object.type == object_type_sphere)
		return (ft_random_point_sphere(object.object.as_sphere));
	else if (object.type == object_type_cylinder)
		return (object.object.as_cylinder.position);
	else if (object.type == object_type_quad)
		return (ft_random_point_quad(object.object.as_quad));
	else if (object.type == object_type_triangle)
		return (ft_random_point_triangle(object.object.as_triangle));
	return ((t_v3f){{0.0f, 0.0f, 0.0f}});
}

#endif