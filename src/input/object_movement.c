/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:08:33 by pberne            #+#    #+#             */
/*   Updated: 2026/02/19 16:49:27 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void ft_move_triangle(t_object *object, t_v3d movement)
{
	object->object.as_triangle.points.a = ft_v3d_add(object->object.as_triangle.points.a, movement);
	object->object.as_triangle.points.b = ft_v3d_add(object->object.as_triangle.points.b, movement);
	object->object.as_triangle.points.c = ft_v3d_add(object->object.as_triangle.points.c, movement);
	object->object.as_triangle = ft_get_processed_triangle(object->object.as_triangle);
	object->bounds = ft_get_triangle_bounds(object->object.as_triangle);
}

int	ft_move_object_2(t_v3d movement, t_object *object, t_data *d,
		int *dirty_bvh)
{
	if (object->type == object_type_triangle)
		ft_move_triangle(object, movement);
	else if (d->selected_object < 0)
		object->object.as_plane.position
			= ft_v3d_add(object->object.as_plane.position, movement);
	else
	{
		ft_move_light((t_light *)object, movement);
		return (0);
	}
	return (1);
}

void	ft_move_light(t_light *light, t_v3d movement)
{
	light->position = ft_v3d_add(light->position, movement);
}

void	ft_move_object(t_v3d movement, t_object *object, t_data *d,
		int *dirty_bvh)
{
	int moved = 0;
	if (object->type == object_type_sphere)
	{
		object->object.as_sphere.position
			= ft_v3d_add(object->object.as_sphere.position, movement);
		object->bounds = ft_get_sphere_bounds(object->object.as_sphere);
	}
	else if (object->type == object_type_cylinder)
	{
		object->object.as_cylinder.position
			= ft_v3d_add(object->object.as_cylinder.position, movement);
		object->bounds = ft_get_cylinder_bounds(object->object.as_cylinder);
	}
	else if (object->type == object_type_quad)
	{
		object->object.as_quad.position
			= ft_v3d_add(object->object.as_quad.position, movement);
		object->bounds = ft_get_quad_bounds(object->object.as_quad);
	}
	else
	{
		*dirty_bvh = ft_move_object_2(movement, object, d, dirty_bvh);
		d->dirty_frame = 1;
		return;
	}
	if (d->selected_object >= 0)
		*dirty_bvh = 1;
	d->dirty_frame = 1;
}
