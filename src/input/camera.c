/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:37:39 by pberne            #+#    #+#             */
/*   Updated: 2026/04/05 20:03:30 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_camera_move(t_data *d)
{
	t_v3f	movement;
	t_v3f	campos;
	t_v3f	camdir;
	float	yaw;

	campos = d->scene->camera.position;
	camdir = d->scene->camera.direction;
	movement.x = ft_get_key(XK_d, d) - ft_get_key(XK_a, d);
	movement.z = ft_get_key(XK_w, d) - ft_get_key(XK_s, d);
	movement.y = ft_get_key(XK_space, d) - ft_get_key(XK_Control_L, d);
	movement.v *= (float)d->deltatime * CAM_MOVEMENT_SPEED * (1.0f + 5.0f
			* (float)ft_get_key(XK_Shift_L, d));
	yaw = atan2f(camdir.x, camdir.z);
	campos.x += sinf(yaw) * movement.z;
	campos.z += cosf(yaw) * movement.z;
	campos.x += cosf(yaw) * movement.x;
	campos.z += -sinf(yaw) * movement.x;
	campos.y += movement.y;
	if (ft_v3f_length(movement) > EPSILON)
		d->dirty_frame = 1;
	d->scene->camera.position = campos;
}

void	ft_camera_rotate(t_data *d)
{
	t_v3f	cam_rot;
	float	rotx;
	float	roty;
	float	key_rot;

	cam_rot = ft_cam_v3f_to_euler(d->scene->camera.direction);
	rotx = d->input.mouse_delta.y * CAM_ROTATION_SPEED * (d->scene->camera.fov
			/ 85.0f);
	key_rot = (float)-ft_get_key(XK_i, d) + (float)ft_get_key(XK_k, d);
	rotx += key_rot * d->deltatime * CAM_ROTATION_SPEED_KEY;
	roty = d->input.mouse_delta.x * CAM_ROTATION_SPEED * (d->scene->camera.fov
			/ 85.0);
	key_rot = (float)-ft_get_key(XK_j, d) + (float)ft_get_key(XK_l, d);
	roty += key_rot * d->deltatime * CAM_ROTATION_SPEED_KEY;
	cam_rot.x = ft_clampd(cam_rot.x + rotx, -85.0, 85.0);
	cam_rot.y = cam_rot.y + roty;
	while (cam_rot.y < -180.0)
		cam_rot.y += 360.0;
	while (cam_rot.y > 180.0)
		cam_rot.y -= 360.0;
	d->scene->camera.direction = ft_cam_euler_to_v3f(cam_rot);
	if (fabs(rotx) > EPSILON || fabs(roty) > EPSILON)
		d->dirty_frame = 1;
}

void	ft_camera_zoom(t_data *d)
{
	if (ft_get_key_down(MOUSE_SCROLL_DOWN, d))
	{
		d->scene->camera.fov *= 1.05f;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(MOUSE_SCROLL_UP, d))
	{
		d->scene->camera.fov *= 0.95f;
		d->dirty_frame = 1;
	}
}
