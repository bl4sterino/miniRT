/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:37:39 by pberne            #+#    #+#             */
/*   Updated: 2026/03/25 17:03:14 by pberne           ###   ########.fr       */
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
	movement.x = ft_get_key(KEY_D, d) - ft_get_key(KEY_A, d);
	movement.z = ft_get_key(KEY_W, d) - ft_get_key(KEY_S, d);
	movement.y = ft_get_key(KEY_SPACE, d) - ft_get_key(KEY_CTRL_L, d);
	movement = ft_v3f_scale(movement, d->deltatime * CAM_MOVEMENT_SPEED);
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
	float	key_roty;

	cam_rot = ft_cam_v3f_to_euler(d->scene->camera.direction);
	rotx = d->input.mouse_delta.y * CAM_ROTATION_SPEED * (d->scene->camera.fov
			/ 85.0f);
	roty = d->input.mouse_delta.x * CAM_ROTATION_SPEED * (d->scene->camera.fov
			/ 85.0);
	key_roty = (float)-ft_get_key(KEY_J, d) + (float)ft_get_key(KEY_K, d);
	roty += key_roty * d->deltatime * CAM_ROTATION_SPEED_KEY;
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
