/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:24:56 by pberne            #+#    #+#             */
/*   Updated: 2026/03/05 15:53:10 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_v3f	ft_get_viewport_target(t_data *d, t_thread_render_context c)
{
	return (ft_v3f_add(d->viewport.top_left,
			ft_v3f_add(ft_v3f_scale(d->viewport.x_delta, (float)c.pixel.x),
				ft_v3f_scale(d->viewport.y_delta, (float)c.pixel.y))));
}

static void	ft_setup_context(t_viewport_context *context, t_camera cam)
{
	context->aspect_ratio = (float)HEIGHT_WIN / (float)WIDTH_WIN;
	context->theta = cam.fov * DEG2RAD;
	context->half_width = tanf(context->theta / 2.0f);
	context->half_height = context->half_width * context->aspect_ratio;
	context->cam_right = ft_v3f_normalize(
			ft_v3f_cross((t_v3f){{0.0f, 1.0f, 0.0f}},
				cam.direction));
	context->cam_up = ft_v3f_cross(cam.direction, context->cam_right);
	context->cam_up = ft_v3f_normalize(context->cam_up);
}

t_viewport	ft_get_viewport(t_camera cam, t_data *d)
{
	t_viewport			vp;
	t_viewport_context	context;
	float				rx;
	float				ry;

	cam.direction = ft_v3f_normalize(cam.direction);
	ft_setup_context(&context, cam);
	vp.u = ft_v3f_scale(context.cam_right, 2.0f * context.half_width);
	vp.v = ft_v3f_scale(context.cam_up, -2.0 * context.half_height);
	vp.x_delta = ft_v3f_div(vp.u, (float)WIDTH_WIN);
	vp.y_delta = ft_v3f_div(vp.v, (float)HEIGHT_WIN);
	vp.top_left = ft_v3f_add(cam.position, cam.direction);
	vp.top_left = ft_v3f_sub(vp.top_left, ft_v3f_scale(vp.u, 0.5f));
	vp.top_left = ft_v3f_sub(vp.top_left, ft_v3f_scale(vp.v, 0.5f));
	rx = tn_f(d->dirty_frame == 0, (float)(rand() % 1000) / 1000.0f, 0.5f);
	ry = tn_f(d->dirty_frame == 0, (float)(rand() % 1000) / 1000.0f, 0.5f);
	context.pixel_center_offset = ft_v3f_add(ft_v3f_scale(vp.x_delta, rx),
			ft_v3f_scale(vp.y_delta, ry));
	vp.top_left = ft_v3f_add(vp.top_left, context.pixel_center_offset);
	vp.bottom_right = ft_v3f_add(vp.top_left, vp.u);
	vp.bottom_right = ft_v3f_add(vp.bottom_right, vp.v);
	vp.top_right = ft_v3f_add(vp.top_left, vp.u);
	vp.bottom_left = ft_v3f_add(vp.top_left, vp.v);
	return (vp);
}
