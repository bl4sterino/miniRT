/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals_inlined.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:41:13 by pberne            #+#    #+#             */
/*   Updated: 2026/02/21 17:00:12 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMALS_INLINED_H
# define NORMALS_INLINED_H

# include "rt.h"

static inline t_v3d	ft_sphere_normal(t_v3d hit_point, t_sphere sphere)
{
	t_v3d	normal;

	normal = ft_v3d_sub(hit_point, sphere.position);
	return (ft_v3d_normalize(normal));
}

static inline t_v3d ft_cylinder_normal(t_v3d hit_point, t_cylinder cyl, t_v3d ray_dir)
{
    t_v3d   v_hit;
    double  projection;
    t_v3d   p_axis;
    t_v3d   normal;

    // 1. Calculate the surface normal (outward facing)
    v_hit = ft_v3d_sub(hit_point, cyl.position);
    projection = ft_v3d_dot(v_hit, cyl.normal);
    p_axis = ft_v3d_add(cyl.position, ft_v3d_scale(cyl.normal, projection));
    normal = ft_v3d_normalize(ft_v3d_sub(hit_point, p_axis));

    // 2. Fix the "Inside" problem
    // If dot product is > 0, the ray and normal are pointing the same way.
    // This means we hit the inner wall, so flip the normal.
    if (ft_v3d_dot(normal, ray_dir) > 0)
    {
        normal = ft_v3d_scale(normal, -1.0);
    }

    return (normal);
}

static inline t_v3d ft_get_sided_normal(t_v3d normal, t_v3d ray_dir)
{
    if (ft_v3d_dot(normal, ray_dir) > 0)
        return (ft_v3d_scale(normal, -1.0));
    return (normal);
}

static inline t_v3d	ft_get_hit_normal(t_v3d hit_point, t_scene *scene, int hit, t_v3d ray_dir)
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
	return ((t_v3d){{0.0, 1.0, 0.0}});
}

#endif
