/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:15:27 by pberne            #+#    #+#             */
/*   Updated: 2026/02/26 15:21:21 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_rotate_cylinder(t_v3f rotation, t_object *object)
{
	object->object.as_cylinder.normal
		= ft_v3f_rotate_worldspace(object->object.as_cylinder.normal, rotation);
	object->bounds = ft_get_cylinder_bounds(object->object.as_cylinder);
}

void	ft_rotate_quad(t_v3f rotation, t_object *object)
{
	object->object.as_quad.normal
		= ft_v3f_rotate_worldspace(object->object.as_quad.normal, rotation);
	object->object.as_quad = ft_get_processed_quad(object->object.as_quad);
	object->bounds = ft_get_quad_bounds(object->object.as_quad);
}

void	ft_rotate_triangle(t_v3f rotation, t_object *object)
{
	t_v3f a;
	t_v3f b;
	t_v3f c;

	a = ft_v3f_sub(object->object.as_triangle.points.a, object->object.as_triangle.position);
	b = ft_v3f_sub(object->object.as_triangle.points.b, object->object.as_triangle.position);
	c = ft_v3f_sub(object->object.as_triangle.points.c, object->object.as_triangle.position);

	a = ft_v3f_rotate_worldspace(a, rotation);
	b = ft_v3f_rotate_worldspace(b, rotation);
	c = ft_v3f_rotate_worldspace(c, rotation);

	object->object.as_triangle.points.a = ft_v3f_add(a, object->object.as_triangle.position);
	object->object.as_triangle.points.b = ft_v3f_add(b, object->object.as_triangle.position);
	object->object.as_triangle.points.c = ft_v3f_add(c, object->object.as_triangle.position);
	
	object->object.as_triangle = ft_get_processed_triangle(object->object.as_triangle);
	object->bounds = ft_get_triangle_bounds(object->object.as_triangle);	
}

void	ft_rotate_object(t_v3f rotation, t_object *object, t_data *d,
		int *dirty_bvh)
{
	if (object->type == object_type_cylinder)
		ft_rotate_cylinder(rotation, object);
	else if (object->type == object_type_quad)
		ft_rotate_quad(rotation, object);
	else if (object->type == object_type_triangle)
		ft_rotate_triangle(rotation, object);
	else if (d->selected_object < 0)
		object->object.as_plane.normal
			= ft_v3f_rotate_worldspace(object->object.as_plane.normal, rotation);
	else
		return ;
	d->dirty_frame = 1;
	if (d->selected_object >= 0)
		*dirty_bvh = 1;
}
