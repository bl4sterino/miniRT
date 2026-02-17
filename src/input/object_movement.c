/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:08:33 by pberne            #+#    #+#             */
/*   Updated: 2026/02/17 15:22:45 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_move_object_2(t_data *d, int *dirty_bvh)
{
	if (d->selected_object >= 0)
		*dirty_bvh = 1;
	d->dirty_frame = 1;
}

void	ft_move_light(t_light *light, t_v3d movement)
{
	light->position = ft_v3d_add(light->position, movement);
}

void	ft_move_object(t_v3d movement, t_object *object, t_data *d,
		int *dirty_bvh)
{
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
	else if (d->selected_object < 0)
		object->object.as_plane.position
			= ft_v3d_add(object->object.as_plane.position, movement);
	else
		ft_move_light((t_light *)object, movement);
	ft_move_object_2(d, dirty_bvh);
}
