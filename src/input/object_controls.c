/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:49:42 by pberne            #+#    #+#             */
/*   Updated: 2026/02/17 15:44:37 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object	*ft_get_selected_object(t_data *d)
{
	if (d->selected_light != -1)
		return ((t_object *)&d->scene->lights[d->selected_light]);
	if (d->selected_object < 0)
		return (&d->scene->planes[-(d->selected_object + 1)]);
	else
		return (&d->scene->raw_objects[d->selected_object]);
}

void	ft_selected_object_controls(t_data *d)
{
	t_v3d		movement;
	t_v3d		rotation;
	t_v3d		extra;
	t_object	*object;
	int			dirty_bvh;

	dirty_bvh = 0;
	movement = ft_get_object_movement(d);
	rotation = ft_get_object_rotation(d);
	extra = ft_get_object_extra(d);
	object = ft_get_selected_object(d);
	if (ft_v3d_length_squared(movement) > EPSILON)
		ft_move_object(movement, object, d, &dirty_bvh);
	if (ft_v3d_length_squared(rotation) > EPSILON)
		ft_rotate_object(rotation, object, d, &dirty_bvh);
	if (ft_v3d_length_squared(extra) > EPSILON)
		ft_extra_controls(extra, object, d, &dirty_bvh);
	if (dirty_bvh > 0)
		d->scene->bvh_root = ft_update_bvh(d->scene, 0, d->scene->num_objects);
}
