/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:37:39 by pberne            #+#    #+#             */
/*   Updated: 2026/01/31 13:00:34 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_camera_move(t_data *d)
{
	t_v3d	movement;
	t_v3d	campos;
	t_v3d	camdir;
	double	yaw;

	campos = d->scene->camera.position;
	camdir = d->scene->camera.direction;
	movement.x = ft_get_key(KEY_D, d) - ft_get_key(KEY_A, d);
	movement.z = ft_get_key(KEY_W, d) - ft_get_key(KEY_S, d);
	movement.y = ft_get_key(KEY_SPACE, d) - ft_get_key(KEY_CTRL_L, d);
	movement = ft_v3d_scale(movement, d->deltatime * CAM_MOVEMENT_SPEED);
	yaw = atan2(camdir.x, camdir.z);
	campos.x += sin(yaw) * movement.z;
	campos.z += cos(yaw) * movement.z;
	campos.x += cos(yaw) * movement.x;
	campos.z += -sin(yaw) * movement.x;
	campos.y += movement.y;
	if (ft_v3d_length(movement) > EPSILON)
		d->dirty_frame = 1;
	d->scene->camera.position = campos;
}

void	ft_camera_rotate(t_data *d)
{
	t_v3d	cam_rot;
	double	rotx;
	double	roty;

	cam_rot = ft_cam_v3d_to_euler(d->scene->camera.direction);
	rotx = d->input.mouse_delta.y * CAM_ROTATION_SPEED * (d->scene->camera.fov
			/ 85.0);
	roty = d->input.mouse_delta.x * CAM_ROTATION_SPEED * (d->scene->camera.fov
			/ 85.0);
	cam_rot.x = ft_clampd(cam_rot.x + rotx, -85.0, 85.0);
	cam_rot.y = cam_rot.y + roty;
	while (cam_rot.y < -180.0)
		cam_rot.y += 360.0;
	while (cam_rot.y > 180.0)
		cam_rot.y -= 360.0;
	d->scene->camera.direction = ft_cam_euler_to_v3d(cam_rot);
	if (fabs(rotx) > EPSILON || fabs(roty) > EPSILON)
		d->dirty_frame = 1;
}
