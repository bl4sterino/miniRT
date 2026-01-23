/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_vectors_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:05:17 by pberne            #+#    #+#             */
/*   Updated: 2026/01/23 12:03:27 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_v3d	ft_cam_v3d_to_euler(t_v3d cam_direction)
{
	t_v3d	euler;
	double	horizontal_dist;

	horizontal_dist = sqrt(cam_direction.x * cam_direction.x + cam_direction.z
			* cam_direction.z);
	euler.x = atan2(-cam_direction.y, horizontal_dist);
	euler.y = atan2(cam_direction.x, cam_direction.z);
	euler.z = 0;
	return (ft_v3d_div(euler, DEG2RAD));
}

t_v3d	ft_cam_euler_to_v3d(t_v3d euler)
{
	t_v3d	forward;
	double	pitch;
	double	yaw;
	double	cos_pitch;

	euler = ft_v3d_scale(euler, DEG2RAD);
	pitch = euler.x;
	yaw = euler.y;
	forward.y = -sin(pitch);
	cos_pitch = cos(pitch);
	forward.x = sin(yaw) * cos_pitch;
	forward.z = cos(yaw) * cos_pitch;
	return (forward);
}

double ft_get_triangle_area(t_v3d A, t_v3d B, t_v3d C)
{
	double v1x = B.x - A.x;
    double v1y = B.y - A.y;
    double v1z = B.z - A.z;

    double v2x = C.x - A.x;
    double v2y = C.y - A.y;
    double v2z = C.z - A.z;

    // 2. Calculate the cross product components
    double cx = (v1y * v2z) - (v1z * v2y);
    double cy = (v1z * v2x) - (v1x * v2z);
    double cz = (v1x * v2y) - (v1y * v2x);

    // 3. Calculate the magnitude of the cross product
    double magnitude = sqrt(cx * cx + cy * cy + cz * cz);

    // 4. Area is half the magnitude
    return 0.5 * magnitude;
}
