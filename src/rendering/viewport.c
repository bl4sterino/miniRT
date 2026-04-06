/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:24:56 by pberne            #+#    #+#             */
/*   Updated: 2026/04/06 21:09:41 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_v3f	ft_get_viewport_target(t_viewport *vp, t_thread_render_context c)
{
	return (ft_v3f_add(vp->top_left,
			ft_v3f_add(ft_v3f_scale(vp->x_delta, (float)c.pixel.x),
				ft_v3f_scale(vp->y_delta, (float)c.pixel.y))));
}

static void	ft_setup_context(t_viewport_context *context, t_camera cam)
{
	context->aspect_ratio = (float)cam.rect.h / (float)cam.rect.w;
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
	vp.x_delta.v = vp.u.v / (float)cam.rect.w;
	vp.y_delta.v = vp.v.v / (float)cam.rect.x;
	vp.raw_top_left.v = cam.position.v + cam.direction.v;
	vp.raw_top_left.v -= vp.u.v * 0.5f;
	vp.raw_top_left.v -= vp.v.v * 0.5f;
	rx = tn_f(d->dirty_frame == 0, (float)(rand() % 1000) / 1000.0f, 0.5f);
	ry = tn_f(d->dirty_frame == 0, (float)(rand() % 1000) / 1000.0f, 0.5f);
	context.pixel_center_offset.v = (vp.x_delta.v * rx) + (vp.y_delta.v * ry);
	vp.top_left.v = vp.raw_top_left.v + context.pixel_center_offset.v;
	vp.bottom_right.v = vp.top_left.v + vp.u.v;
	vp.bottom_right.v = vp.bottom_right.v + vp.v.v;
	vp.top_right.v = vp.top_left.v + vp.u.v;
	vp.bottom_left.v = vp.top_left.v + vp.v.v;
	return (vp);
}
