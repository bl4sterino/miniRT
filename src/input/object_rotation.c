/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:15:27 by pberne            #+#    #+#             */
/*   Updated: 2026/04/09 19:28:16 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_rotate_cylinder(t_v3f rotation, t_object *object)
{
	object->object.as_cylinder.normal = ft_v3f_rotate_worldspace
		(object->object.as_cylinder.normal, rotation);
	object->object.as_cylinder
		= ft_get_processed_cylinder(object->object.as_cylinder);
	object->bounds = ft_get_cylinder_bounds(object->object.as_cylinder);
}

void	ft_rotate_quad(t_v3f rotation, t_object *object)
{
	object->object.as_quad.normal = ft_v3f_rotate_worldspace(
			object->object.as_quad.normal, rotation);
	object->object.as_quad = ft_get_processed_quad(object->object.as_quad);
	object->bounds = ft_get_quad_bounds(object->object.as_quad);
}

void	ft_rotate_triangle(t_v3f rotation, t_object *object)
{
	t_v3f	a;
	t_v3f	b;
	t_v3f	c;

	a.v = object->object.as_triangle.points[0].v
		- object->object.as_triangle.position.v;
	b.v = object->object.as_triangle.points[1].v
		- object->object.as_triangle.position.v;
	c.v = object->object.as_triangle.points[2].v
		- object->object.as_triangle.position.v;
	a = ft_v3f_rotate_worldspace(a, rotation);
	b = ft_v3f_rotate_worldspace(b, rotation);
	c = ft_v3f_rotate_worldspace(c, rotation);
	object->object.as_triangle.points[0].v = a.v
		+ object->object.as_triangle.position.v;
	object->object.as_triangle.points[1].v = b.v
		+ object->object.as_triangle.position.v;
	object->object.as_triangle.points[2].v = c.v
		+ object->object.as_triangle.position.v;
	object->object.as_triangle = ft_get_processed_triangle(
			object->object.as_triangle);
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
		object->object.as_plane.normal = ft_v3f_rotate_worldspace(
				object->object.as_plane.normal, rotation);
	else
		return ;
	d->dirty_frame = 1;
	if (d->selected_object >= 0)
		*dirty_bvh = 1;
}
