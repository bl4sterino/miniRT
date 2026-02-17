/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:10:22 by pberne            #+#    #+#             */
/*   Updated: 2026/02/17 15:58:04 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_extra_sphere(t_v3d extra, t_object *object, t_data *d,
		int *dirty_bvh)
{
	if (ft_dabs(extra.x) < EPSILON)
		return ;
	object->object.as_sphere.radius += extra.x;
	object->bounds = ft_get_sphere_bounds(object->object.as_sphere);
	d->dirty_frame = 1;
	*dirty_bvh = 1;
}

void	ft_extra_cylinder(t_v3d extra, t_object *object, t_data *d,
		int *dirty_bvh)
{
	if (ft_dabs(extra.x) < EPSILON && ft_dabs(extra.y) < EPSILON)
		return ;
	object->object.as_cylinder.diameter += extra.x *0.5f;
	object->object.as_cylinder.height += extra.y;
	object->bounds = ft_get_cylinder_bounds(object->object.as_cylinder);
	d->dirty_frame = 1;
	*dirty_bvh = 1;
}

void	ft_extra_quad(t_v3d extra, t_object *object, t_data *d, int *dirty_bvh)
{
	if (ft_dabs(extra.x) < EPSILON && ft_dabs(extra.y) < EPSILON)
		return ;
	object->object.as_quad.size.x += extra.x;
	object->object.as_quad.size.y += extra.y;
	object->bounds = ft_get_quad_bounds(object->object.as_quad);
	d->dirty_frame = 1;
	*dirty_bvh = 1;
}

void	ft_extra_controls(t_v3d extra, t_object *object, t_data *d,
		int *dirty_bvh)
{
	if (object->type == object_type_sphere)
		ft_extra_sphere(extra, object, d, dirty_bvh);
	else if (object->type == object_type_cylinder)
		ft_extra_cylinder(extra, object, d, dirty_bvh);
	else if (object->type == object_type_quad)
		ft_extra_quad(extra, object, d, dirty_bvh);
}
