/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals_inlined.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:41:13 by pberne            #+#    #+#             */
/*   Updated: 2026/02/27 16:25:24 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMALS_INLINED_H
# define NORMALS_INLINED_H

# include "rt.h"

static inline t_v3f	ft_sphere_normal(t_v3f hit_point, t_sphere sphere)
{
	t_v3f	normal;

	normal = ft_v3f_sub(hit_point, sphere.position);
    if (ft_v3f_length_squared(normal) > sphere.radius * sphere.radius)
        normal = ft_v3f_scale(normal, -1.0f);
	return (ft_v3f_normalize(normal));
}

static inline t_v3f ft_cylinder_normal(t_v3f hit_point, t_cylinder cyl, t_v3f ray_dir)
{
    t_v3f   v_hit;
    float  projection;
    t_v3f   p_axis;
    t_v3f   normal;

    // 1. Calculate the surface normal (outward facing)
    v_hit = ft_v3f_sub(hit_point, cyl.position);
    projection = ft_v3f_dot(v_hit, cyl.normal);
    p_axis = ft_v3f_add(cyl.position, ft_v3f_scale(cyl.normal, projection));
    normal = ft_v3f_normalize(ft_v3f_sub(hit_point, p_axis));

    // 2. Fix the "Inside" problem
    // If dot product is > 0, the ray and normal are pointing the same way.
    // This means we hit the inner wall, so flip the normal.
    if (ft_v3f_dot(normal, ray_dir) > 0.0f)
    {
        normal = ft_v3f_scale(normal, -1.0f);
    }

    return (normal);
}

static inline t_v3f ft_get_sided_normal(t_v3f normal, t_v3f ray_dir)
{
    if (ft_v3f_dot(normal, ray_dir) > 0.0f)
        return (ft_v3f_scale(normal, -1.0f));
    return (normal);
}

static inline t_v3f	ft_get_hit_normal(t_v3f hit_point, t_scene *scene, int hit, t_v3f ray_dir)
{
	t_object	object;

	if (hit < 0)
		return (ft_get_sided_normal(scene->planes[-hit - 1].object.as_plane.normal, ray_dir));
	object = scene->objects[hit];
	if (object.type == object_type_sphere)
        return (ft_sphere_normal(hit_point, object.object.as_sphere));
	else if (object.type == object_type_cylinder)
		return (ft_cylinder_normal(hit_point, object.object.as_cylinder, ray_dir));
	else if (object.type == object_type_quad)
		return (ft_get_sided_normal(object.object.as_quad.normal, ray_dir));
	else if (object.type == object_type_triangle)
		return (ft_get_sided_normal(object.object.as_triangle.normal, ray_dir));
	return ((t_v3f){{0.0f, 1.0f, 0.0f}});
}

#endif
