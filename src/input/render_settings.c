/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:58:33 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 19:17:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_render_settings_3(t_data *d, t_camera *cam)
{
	if (ft_get_key(XK_0, d) - ft_get_key(XK_9, d))
	{
		cam->stereo_offset += 5.0f * d->deltatime * (float)(ft_get_key(XK_0, d)
				- ft_get_key(XK_9, d));
		cam->dirty = 1;
	}
	if (ft_get_key_down(XK_v, d))
	{
		if (cam->render_mode == RENDER_RAY_TARGETS)
			cam->render_mode = RENDER_DEFAULT;
		else
			cam->render_mode = RENDER_RAY_TARGETS;
		cam->dirty = 1;
	}
	ft_dof_settings(d, cam);
}

void	ft_render_settings_2(t_data *d, t_camera *cam)
{
	if (ft_get_key_down(XK_n, d))
	{
		if (cam->render_mode == RENDER_NORMALS)
			cam->render_mode = RENDER_DEFAULT;
		else
			cam->render_mode = RENDER_NORMALS;
		cam->dirty = 1;
	}
	if (ft_get_key_down(XK_m, d))
	{
		cam->stereo = !cam->stereo;
		cam->dirty = 1;
	}
	if (ft_get_key(XK_bracketleft, d))
	{
		cam->stereo_space *= 1.0f - ft_clampf(0.5f * d->deltatime, 0.0f, 0.5f);
		cam->dirty = 1;
	}
	if (ft_get_key(XK_bracketright, d))
	{
		cam->stereo_space *= 1.0f + 0.5f * d->deltatime;
		cam->dirty = 1;
	}
	ft_render_settings_3(d, cam);
}

void	ft_render_settings(t_data *d)
{
	t_camera	*cam;

	cam = get_active_camera(d->scene);
	if (ft_get_key_down(XK_e, d))
	{
		if (cam->render_mode == RENDER_BVH)
			cam->render_mode = RENDER_DEFAULT;
		else
			cam->render_mode = RENDER_BVH;
		cam->dirty = 1;
	}
	if (ft_get_key_down(XK_f, d))
	{
		d->target_ray_bounces = ft_max(0, d->target_ray_bounces
				- tn_i(ft_get_key(MOUSE_RIGHT, d), 10, 1));
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(XK_g, d))
	{
		d->target_ray_bounces += tn_i(ft_get_key(MOUSE_RIGHT, d), 10, 1);
		d->dirty_frame = 1;
	}
	ft_render_settings_2(d, cam);
}
