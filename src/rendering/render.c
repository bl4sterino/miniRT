/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:52:25 by pberne            #+#    #+#             */
/*   Updated: 2026/01/23 08:04:49 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_render(t_data *d)
{
	t_v3d x_delta;
	t_v3d y_delta;
	t_v3d top_left;
	t_camera cam;

	cam = d->scene->camera;

	double aspect_ratio = (double)HEIGHT_WIN / (double)WIDTH_WIN;
	double theta = cam.fov * DEG2RAD;
	double half_width = tan(theta / 2.0);
	double half_height = half_width * aspect_ratio;

	t_v3d right = ft_v3d_normalize(ft_v3d_cross(cam.direction, (t_v3d){0.0, 1.0, 0.0}));
	t_v3d up = ft_v3d_cross(right, cam.direction);

	t_v3d viewport_x = ft_v3d_scale(right, 2.0 * half_width);
	t_v3d viewport_y = ft_v3d_scale(up, -2.0 * half_height);

	x_delta = ft_v3d_div(viewport_x, WIDTH_WIN);
	y_delta = ft_v3d_div(viewport_y, HEIGHT_WIN);

	t_v3d half_u = ft_v3d_div(viewport_x, 2.0);
	t_v3d half_v = ft_v3d_div(viewport_y, 2.0);

	top_left = ft_v3d_add(cam.position, cam.direction);
	top_left = ft_v3d_sub(top_left, half_u);
	top_left = ft_v3d_sub(top_left, half_v);

	t_v3d pixel_center_offset = ft_v3d_add(x_delta, y_delta);
	pixel_center_offset = ft_v3d_scale(pixel_center_offset, 0.5);
	top_left = ft_v3d_add(top_left, pixel_center_offset);


	ft_clock_start(clock_render);
	(void)d;
	ft_clock_set(clock_render);
}
