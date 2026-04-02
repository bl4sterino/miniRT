/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:18:09 by pberne            #+#    #+#             */
/*   Updated: 2026/04/02 17:15:28 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISIONS_H
# define COLLISIONS_H

# include "collision_bounds.h"
# include "collision_cylinder.h"
# include "collision_plane.h"
# include "collision_quad.h"
# include "collision_sphere.h"
# include "collision_triangle.h"
# include "collisions_ellipsoid.h"
# include "rt.h"

static inline void	ft_check_objects_collisions(t_ray ray, int object_index,
		t_bvh_context *context, t_object *obj)
{
	float	dist;

	dist = FT_INFINITY;
	if (obj->type == object_type_quad)
		dist = ft_quad_collision(ray, obj->object.as_quad);
	else if (obj->type == object_type_sphere)
		dist = ft_sphere_collision(ray, obj->object.as_sphere);
	else if (obj->type == object_type_cylinder)
		dist = ft_cylinder_collision(ray, obj->object.as_cylinder);
	else if (obj->type == object_type_triangle)
		dist = ft_triangle_collision(ray, obj->object.as_triangle);
	else if (obj->type == object_type_ellipsoid)
		dist = ft_ellipsoid_collision(ray, obj->object.as_ellipsoid);
	if (dist < context->best_dist)
	{
		context->best_dist = dist;
		context->best_index = object_index;
	}
}

static inline float	ft_get_object_distance(t_ray ray, t_scene *scene,
		int object_id, int *hit)
{
	t_object	*obj;
	float		dist;

	*hit = object_id;
	dist = FT_INFINITY;
	if (object_id < 0)
		return (ft_plane_collision(ray, scene->planes[-object_id
					- 1].object.as_plane));
	else
		obj = &scene->objects[object_id];
	if (obj->type == object_type_quad)
		dist = ft_quad_collision(ray, obj->object.as_quad);
	else if (obj->type == object_type_sphere)
		dist = ft_sphere_collision(ray, obj->object.as_sphere);
	else if (obj->type == object_type_cylinder)
		dist = ft_cylinder_collision(ray, obj->object.as_cylinder);
	else if (obj->type == object_type_triangle)
		dist = ft_triangle_collision(ray, obj->object.as_triangle);
	else if (obj->type == object_type_ellipsoid)
		dist = ft_ellipsoid_collision(ray, obj->object.as_ellipsoid);
	return (dist);
}

#endif
