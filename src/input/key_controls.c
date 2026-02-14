/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:48:05 by pberne            #+#    #+#             */
/*   Updated: 2026/02/14 14:43:12 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_get_object_at(t_data *d, t_v2i screenpos)
{
	t_ray	ray;
	t_v3d	target;
	t_v3d	x_offset;
	t_v3d	y_offset;
	int		hit;

	if (screenpos.x < 0 || screenpos.x >= WIDTH_WIN || screenpos.y < 0
		|| screenpos.y > HEIGHT_WIN)
		return;
	ray.origin = d->scene->camera.position;
	target = d->viewport.top_left;
	x_offset = ft_v3d_scale(d->viewport.x_delta, (double)screenpos.x);
	y_offset = ft_v3d_scale(d->viewport.y_delta, (double)screenpos.y);
	target = ft_v3d_add(target, x_offset);
	target = ft_v3d_add(target, y_offset);
	ray = ft_setup_ray_direction(ray, ft_v3d_sub(target, ray.origin), 0);
	hit = SELECTED_NONE;
	ft_shoot_ray(ray, d->scene, &hit);
	d->selected_object = hit;
}

void	ft_controls(t_data *d)
{
	ft_debug_gc(d);
	if (ft_get_key_down(KEY_E, d))
	{
		d->render_mode = !d->render_mode;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(MOUSE_SCROLL_DOWN, d))
	{
		d->scene->camera.fov *= 1.05;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(MOUSE_SCROLL_UP, d))
	{
		d->scene->camera.fov *= 0.95;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(MOUSE_LEFT, d))
	{
		ft_get_object_at(d, d->input.mouse_pos);
	}
}
