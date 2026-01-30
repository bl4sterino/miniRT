/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals_inlined.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:41:13 by pberne            #+#    #+#             */
/*   Updated: 2026/01/30 12:31:29 by pberne           ###   ########.fr       */
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

static inline t_v3d	ft_cylinder_normal(t_v3d hit_point, t_cylinder cyl)
{
	t_v3d	v_hit;
	double	projection;
	t_v3d	p_axis;
	t_v3d	normal;

	v_hit = ft_v3d_sub(hit_point, cyl.position);
	projection = ft_v3d_dot(v_hit, cyl.normal);
	p_axis = ft_v3d_add(cyl.position, ft_v3d_scale(cyl.normal, projection));
	normal = ft_v3d_sub(hit_point, p_axis);
	return (ft_v3d_normalize(normal));
}

static inline t_v3d	ft_get_hit_normal(t_v3d hit_point, t_scene *scene, int hit)
{
	t_object	object;

	if (hit < 0)
		return (scene->planes[-hit - 1].object.as_plane.normal);
	object = scene->objects[hit];
	if (object.type == object_type_sphere)
		return (ft_sphere_normal(hit_point, object.object.as_sphere));
	if (object.type == object_type_cylinder)
		return (ft_cylinder_normal(hit_point, object.object.as_cylinder));
	return (object.object.as_quad.normal);
}

#endif
