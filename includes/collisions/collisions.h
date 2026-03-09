/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:18:09 by pberne            #+#    #+#             */
/*   Updated: 2026/03/09 13:22:03 by pberne           ###   ########.fr       */
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
	else if (obj->type == object_type_ellopsoid)
		dist = ft_ellipsoid_collision(ray, obj->object.as_ellipsoid);
	if (dist < context->best_dist)
	{
		context->best_dist = dist;
		context->best_index = object_index;
	}
}

#endif
