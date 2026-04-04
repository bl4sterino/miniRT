/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_selection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:30:46 by pberne            #+#    #+#             */
/*   Updated: 2026/04/04 20:57:12 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_get_object_at(t_data *d, t_v2i screenpos)
{
	t_ray	ray;
	t_v3f	target;
	t_v3f	x_offset;
	t_v3f	y_offset;
	int		hit;

	if (screenpos.x < 0 || screenpos.x >= WIDTH_WIN || screenpos.y < 0
		|| screenpos.y > HEIGHT_WIN)
		return ;
	ray.origin = d->scene->camera.position;
	target = d->viewport.top_left;
	x_offset = ft_v3f_scale(d->viewport.x_delta, (double)screenpos.x);
	y_offset = ft_v3f_scale(d->viewport.y_delta, (double)screenpos.y);
	target = ft_v3f_add(target, x_offset);
	target = ft_v3f_add(target, y_offset);
	ray = ft_setup_ray_direction(ray, ft_v3f_sub(target, ray.origin), 0, 0);
	hit = SELECTED_NONE;
	ft_shoot_ray(ray, d->scene, &hit);
	if (hit >= 0 && hit != SELECTED_NONE)
		hit = d->scene->objects[hit].raw_id;
	d->selected_object = hit;
	d->selected_light = -1;
}

void	ft_try_select_light(t_data *d)
{
	int	direction;

	direction = ft_get_key_down(XK_Page_Up, d) - ft_get_key_down(XK_Page_Down,
			d);
	if (direction && d->scene->num_lights > 0)
	{
		d->selected_object = SELECTED_NONE;
		if (d->selected_light == -1)
			d->selected_light = tn_i(direction < 0, d->scene->num_lights - 1,
					0);
		else
		{
			d->selected_light += direction;
			if (d->selected_light < 0)
				d->selected_light += d->scene->num_lights;
			if (d->selected_light >= d->scene->num_lights)
				d->selected_light = 0;
		}
	}
}

void	ft_select_objects(t_data *d)
{
	if (ft_get_key_down(MOUSE_LEFT, d))
		ft_get_object_at(d, d->input.mouse_pos);
	ft_try_select_light(d);
}
