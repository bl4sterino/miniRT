/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:37:39 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 11:37:27 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_camera_init(t_data *d, t_v3f pos, t_v3f rot)
{
	d->cam.speed = CAM_MOVEMENT_SPEED;
	d->cam.t.pos.x = CAM_X;
	d->cam.t.pos.y = CAM_Y;
	d->cam.t.pos.z = CAM_Z;
	d->cam.t.rot.x = 0.0f;
	d->cam.t.rot.y = 0.0f;
	d->cam.t.rot.z = 0.0f;
	ft_update_rotation_data(d);
}

void	ft_camera_move(t_data *d)
{

}

void	ft_camera_rotate(t_data *d)
{
	
}

void	ft_display_camera_transform(t_data *d)
{
	ft_draw_double(d, (t_draw_arg){(t_v2i){100, 0}, (t_v2i){70, 15}, (t_rgb){50,
		50, 50}}, "x: ", (double)d->cam.t.rot.x);
	ft_draw_double(d, (t_draw_arg){(t_v2i){170, 0}, (t_v2i){70, 15}, (t_rgb){50,
		50, 50}}, "y: ", (double)d->cam.t.rot.y);
	ft_draw_double(d, (t_draw_arg){(t_v2i){240, 0}, (t_v2i){70, 15}, (t_rgb){50,
		50, 50}}, "z: ", (double)d->cam.t.rot.z);
	ft_draw_double(d, (t_draw_arg){(t_v2i){400, 0}, (t_v2i){70, 15}, (t_rgb){50,
		50, 50}}, "x: ", (double)d->cam.t.pos.x);
	ft_draw_double(d, (t_draw_arg){(t_v2i){470, 0}, (t_v2i){70, 15}, (t_rgb){50,
		50, 50}}, "y: ", (double)d->cam.t.pos.y);
	ft_draw_double(d, (t_draw_arg){(t_v2i){540, 0}, (t_v2i){70, 15}, (t_rgb){50,
		50, 50}}, "z: ", (double)d->cam.t.pos.z);
	ft_draw_double(d, (t_draw_arg){(t_v2i){100, 15}, (t_v2i){90, 15},
		(t_rgb){50, 50, 50}}, "speed: ", (double)d->cam.speed);
	ft_draw_str(d, (t_draw_arg){(t_v2i){0, 0}, (t_v2i){70, 15},
		(t_rgb){50, 50, 50}}, d->fpsstr);
	ft_draw_double(d, (t_draw_arg){(t_v2i){100, 30}, (t_v2i){90, 15},
		(t_rgb){50, 50, 50}}, "fov: ", (double)d->cam.fov);
}
