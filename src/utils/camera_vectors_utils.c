/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_vectors_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:05:17 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 15:39:31 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_v3f	ft_cam_v3f_to_euler(t_v3f cam_direction)
{
	t_v3f	euler;
	float	horizontal_dist;

	horizontal_dist = sqrtf(cam_direction.x * cam_direction.x + cam_direction.z
			* cam_direction.z);
	euler.x = atan2f(-cam_direction.y, horizontal_dist);
	euler.y = atan2f(cam_direction.x, cam_direction.z);
	euler.z = 0.0f;
	return (ft_v3f_div(euler, DEG2RAD));
}

t_v3f	ft_cam_euler_to_v3f(t_v3f euler)
{
	t_v3f	forward;
	float	pitch;
	float	yaw;
	float	cos_pitch;

	euler = ft_v3f_scale(euler, DEG2RAD);
	pitch = euler.x;
	yaw = euler.y;
	forward.y = -sinf(pitch);
	cos_pitch = cosf(pitch);
	forward.x = sinf(yaw) * cos_pitch;
	forward.z = cosf(yaw) * cos_pitch;
	return (forward);
}
