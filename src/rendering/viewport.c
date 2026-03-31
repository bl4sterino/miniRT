/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:24:56 by pberne            #+#    #+#             */
/*   Updated: 2026/03/28 19:18:13 by pberne           ###   ########.fr       */
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
	context->cam_right = ft_v3f_normalize(ft_v3f_cross((t_v3f){{0.0f, 1.0f,
				0.0f}}, cam.direction));
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
	vp.u.v = context.cam_right.v * 2.0f * context.half_width;
	vp.v.v = context.cam_up.v * -2.0f * context.half_height;
	vp.x_delta.v = vp.u.v / (float)WIDTH_WIN;
	vp.y_delta.v = vp.v.v / (float)HEIGHT_WIN;
	vp.top_left.v = cam.position.v + cam.direction.v;
	vp.top_left.v -= vp.u.v * 0.5f;
	vp.top_left.v -= vp.v.v * 0.5f;
	rx = tn_f(d->dirty_frame == 0, (float)(rand() % 1000) / 1000.0f, 0.5f);
	ry = tn_f(d->dirty_frame == 0, (float)(rand() % 1000) / 1000.0f, 0.5f);
	context.pixel_center_offset.v = (vp.x_delta.v * rx) + (vp.y_delta.v * ry);
	vp.top_left.v = vp.top_left.v + context.pixel_center_offset.v;
	vp.bottom_right.v = vp.top_left.v + vp.u.v;
	vp.bottom_right.v = vp.bottom_right.v + vp.v.v;
	vp.top_right.v = vp.top_left.v + vp.u.v;
	vp.bottom_left.v = vp.top_left.v + vp.v.v;
	return (vp);
}
