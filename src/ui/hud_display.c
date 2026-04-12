/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:03:34 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 19:18:24 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_draw_cam_data(t_data *d)
{
	t_v3f		rot;
	t_v3f		pos;
	t_camera	*cam;

	cam = get_active_camera(d->scene);
	pos = cam->position;
	rot = ft_cam_v3f_to_euler(cam->direction);
	ft_draw_double(d, (t_draw_arg){(t_v2i){100, 0}, (t_v2i){80, 15}, (t_rgb){50,
		50, 50}}, "pos X: ", pos.x);
	ft_draw_double(d, (t_draw_arg){(t_v2i){180, 0}, (t_v2i){80, 15}, (t_rgb){50,
		50, 50}}, "pos Y: ", pos.y);
	ft_draw_double(d, (t_draw_arg){(t_v2i){260, 0}, (t_v2i){80, 15}, (t_rgb){50,
		50, 50}}, "pos Z: ", pos.z);
	ft_draw_double(d, (t_draw_arg){(t_v2i){340, 0}, (t_v2i){80, 15}, (t_rgb){50,
		50, 50}}, "rot X: ", rot.x);
	ft_draw_double(d, (t_draw_arg){(t_v2i){420, 0}, (t_v2i){80, 15}, (t_rgb){50,
		50, 50}}, "rot Y: ", rot.y);
	ft_draw_double(d, (t_draw_arg){(t_v2i){500, 0}, (t_v2i){80, 15}, (t_rgb){50,
		50, 50}}, "rot Z: ", rot.z);
}

void	ft_draw_clocks(t_data *d)
{
	ft_draw_double_8(d, (t_draw_arg){(t_v2i){0, HEIGHT_WIN - 15}, (t_v2i){170,
		15}, (t_rgb){50, 50, 50}}, "Frame Duration: ",
		ft_clock_get(clock_frame));
	ft_draw_int(d, (t_draw_arg){(t_v2i){170, HEIGHT_WIN - 15}, (t_v2i){80, 15},
		(t_rgb){50, 50, 50}}, "Bounces: ", d->ray_bounces);
	ft_draw_double_8(d, (t_draw_arg){(t_v2i){260, HEIGHT_WIN - 15}, (t_v2i){170,
		15}, (t_rgb){50, 50, 50}}, "Stereo Offset: ",
		d->scene->cameras[d->scene->active_camera].stereo_offset);
	ft_draw_double_8(d, (t_draw_arg){(t_v2i){430, HEIGHT_WIN - 15}, (t_v2i){170,
		15}, (t_rgb){50, 50, 50}}, "Eye Dist: ",
		d->scene->cameras[d->scene->active_camera].stereo_space);
	ft_draw_double_8(d, (t_draw_arg){(t_v2i){610, HEIGHT_WIN - 15}, (t_v2i){170,
		15}, (t_rgb){50, 50, 50}}, "Aperture: ",
		d->scene->cameras[d->scene->active_camera].aperture);
	ft_draw_double_8(d, (t_draw_arg){(t_v2i){780, HEIGHT_WIN - 15}, (t_v2i){170,
		15}, (t_rgb){50, 50, 50}}, "Focus Dist: ",
		d->scene->cameras[d->scene->active_camera].focus_distance);
}

void	ft_hud_display(t_data *d)
{
	ft_draw_str(d, (t_draw_arg){(t_v2i){0, 0}, (t_v2i){80, 15}, (t_rgb){50, 50,
		50}}, d->fpsstr);
	ft_draw_cam_data(d);
	ft_draw_clocks(d);
}
