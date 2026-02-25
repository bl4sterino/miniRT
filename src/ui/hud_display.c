/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:03:34 by pberne            #+#    #+#             */
/*   Updated: 2026/02/25 11:32:10 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_draw_cam_data(t_data *d)
{
	t_v3d	rot;
	t_v3d	pos;

	pos = d->scene->camera.position;
	rot = ft_cam_v3d_to_euler(d->scene->camera.direction);
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
		15}, (t_rgb){50, 50, 50}}, "frame duration: ",
		ft_clock_get(clock_frame));
	ft_draw_double_8(d, (t_draw_arg){(t_v2i){170, HEIGHT_WIN - 15}, (t_v2i){170,
		15}, (t_rgb){50, 50, 50}}, "Denoiser: ",
		ft_clock_get(clock_blur));
}

void	ft_hud_display(t_data *d)
{
	ft_draw_str(d, (t_draw_arg){(t_v2i){0, 0}, (t_v2i){80, 15}, (t_rgb){50, 50,
		50}}, d->fpsstr);
	ft_draw_cam_data(d);
	ft_draw_clocks(d);
}
