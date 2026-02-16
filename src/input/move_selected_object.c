/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_selected_object.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:49:42 by pberne            #+#    #+#             */
/*   Updated: 2026/02/16 18:38:54 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_move_selected_object(t_data *d)
{
	t_v3d movement;
	
	movement.x = ft_get_key(KEY_RIGHT, d) - ft_get_key(KEY_LEFT, d);
	movement.z = ft_get_key(KEY_UP, d) - ft_get_key(KEY_DOWN, d);
	movement.y = ft_get_key(KEY_KP_PLUS, d) - ft_get_key(KEY_KP_MINUS, d);

	if (ft_v3d_length(movement) > EPSILON)
		movement = ft_v3d_normalize(movement);
	else
		return;
	movement = ft_v3d_scale(movement, OBJ_MOVEMENT_SPEED * d->deltatime);


	t_object *object;
	if(d->selected_object < 0)
		object = &d->scene->planes[-(d->selected_object + 1)];
	else
		object = &d->scene->raw_objects[d->selected_object];
	if (object->type == object_type_sphere)
	{
			object->object.as_sphere.position = ft_v3d_add(object->object.as_sphere.position, movement);
			object->bounds = ft_get_sphere_bounds(object->object.as_sphere);
	}
	else if (object->type == object_type_cylinder)
	{
			object->object.as_cylinder.position = ft_v3d_add(object->object.as_cylinder.position, movement);
			object->bounds = ft_get_cylinder_bounds(object->object.as_cylinder);
	}
	else if (object->type == object_type_quad)
	{
			object->object.as_quad.position = ft_v3d_add(object->object.as_quad.position, movement);
			object->bounds = ft_get_quad_bounds(object->object.as_quad);
	}
	else if(d->selected_object < 0)
	{
			object->object.as_plane.position = ft_v3d_add(object->object.as_plane.position, movement);
	}
	d->dirty_frame = 1;
	if (d->selected_object >= 0)
		d->scene->bvh_root = ft_update_bvh(d->scene, 0, d->scene->num_objects);
}
