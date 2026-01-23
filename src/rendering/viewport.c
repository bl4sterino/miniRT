/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:24:56 by pberne            #+#    #+#             */
/*   Updated: 2026/01/23 15:15:07 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_setup_context(t_viewport_context *context, t_camera cam)
{
	context->aspect_ratio = (double)HEIGHT_WIN / (double)WIDTH_WIN;
	context->theta = cam.fov * DEG2RAD;
	context->half_width = tan(context->theta / 2.0);
	context->half_height = context->half_width * context->aspect_ratio;
	context->cam_right = ft_v3d_normalize(ft_v3d_cross((t_v3d){0.0, 1.0, 0.0},
				cam.direction));
	context->cam_up = ft_v3d_cross(cam.direction, context->cam_right);
	context->cam_up = ft_v3d_normalize(context->cam_up);
}

t_viewport	ft_get_viewport(t_camera cam)
{
	t_viewport			viewport;
	t_viewport_context	context;

	cam.direction = ft_v3d_normalize(cam.direction);
	ft_setup_context(&context, cam);
	viewport.u = ft_v3d_scale(context.cam_right, 2.0 * context.half_width);
	viewport.v = ft_v3d_scale(context.cam_up, -2.0 * context.half_height);
	viewport.x_delta = ft_v3d_div(viewport.u, (double)WIDTH_WIN);
	viewport.y_delta = ft_v3d_div(viewport.v, (double)HEIGHT_WIN);
	viewport.top_left = ft_v3d_add(cam.position, cam.direction);
	viewport.top_left = ft_v3d_sub(viewport.top_left, ft_v3d_scale(viewport.u,
				0.5));
	viewport.top_left = ft_v3d_sub(viewport.top_left, ft_v3d_scale(viewport.v,
				0.5));
	context.pixel_center_offset = ft_v3d_add(viewport.x_delta,
			viewport.y_delta);
	context.pixel_center_offset = ft_v3d_scale(context.pixel_center_offset,
			0.5);
	viewport.top_left = ft_v3d_add(viewport.top_left,
			context.pixel_center_offset);
	viewport.bottom_right = ft_v3d_add(viewport.top_left, viewport.u);
	viewport.bottom_right = ft_v3d_add(viewport.bottom_right, viewport.v);
	viewport.top_right = ft_v3d_add(viewport.top_left, viewport.u);
	viewport.bottom_left = ft_v3d_add(viewport.top_left, viewport.v);
	return (viewport);
}
