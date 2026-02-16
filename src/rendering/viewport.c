/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:24:56 by pberne            #+#    #+#             */
/*   Updated: 2026/02/16 18:44:22 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_setup_context(t_viewport_context *context, t_camera cam)
{
	context->aspect_ratio = (double)HEIGHT_WIN / (double)WIDTH_WIN;
	context->theta = cam.fov * DEG2RAD;
	context->half_width = tan(context->theta / 2.0);
	context->half_height = context->half_width * context->aspect_ratio;
	context->cam_right = ft_v3d_normalize(ft_v3d_cross((t_v3d){{0.0, 1.0, 0.0}},
				cam.direction));
	context->cam_up = ft_v3d_cross(cam.direction, context->cam_right);
	context->cam_up = ft_v3d_normalize(context->cam_up);
}

t_viewport	ft_get_viewport(t_camera cam, t_data *d)
{
	t_viewport			vp;
	t_viewport_context	context;
	double				rx;
	double				ry;

	cam.direction = ft_v3d_normalize(cam.direction);
	ft_setup_context(&context, cam);
	vp.u = ft_v3d_scale(context.cam_right, 2.0 * context.half_width);
	vp.v = ft_v3d_scale(context.cam_up, -2.0 * context.half_height);
	vp.x_delta = ft_v3d_div(vp.u, (double)WIDTH_WIN);
	vp.y_delta = ft_v3d_div(vp.v, (double)HEIGHT_WIN);
	vp.top_left = ft_v3d_add(cam.position, cam.direction);
	vp.top_left = ft_v3d_sub(vp.top_left, ft_v3d_scale(vp.u, 0.5));
	vp.top_left = ft_v3d_sub(vp.top_left, ft_v3d_scale(vp.v, 0.5));
	rx = tn_d(d->dirty_frame == 0, (double)(rand() % 1000) / 1000.0, 0.5);
	ry = tn_d(d->dirty_frame == 0, (double)(rand() % 1000) / 1000.0, 0.5);
	context.pixel_center_offset = ft_v3d_add(ft_v3d_scale(vp.x_delta, rx),
			ft_v3d_scale(vp.y_delta, ry));
	vp.top_left = ft_v3d_add(vp.top_left, context.pixel_center_offset);
	vp.bottom_right = ft_v3d_add(vp.top_left, vp.u);
	vp.bottom_right = ft_v3d_add(vp.bottom_right, vp.v);
	vp.top_right = ft_v3d_add(vp.top_left, vp.u);
	vp.bottom_left = ft_v3d_add(vp.top_left, vp.v);
	return (vp);
}
