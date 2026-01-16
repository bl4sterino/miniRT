/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:12:48 by pberne            #+#    #+#             */
/*   Updated: 2025/12/06 19:47:43 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_multiply_z(t_data *d, float sign)
{
	int		i;
	float	coef;

	i = 0;
	coef = 1.0f + SCALING_COEF * d->deltatime * sign;
	while (i < d->map.point_count)
	{
		d->map.points[i].pos.z *= coef;
		i++;
	}
	d->map.flag_for_rebake = 1;
}

// Tanslates and rotate to transform a vector into camera space
t_v3f	ft_world_to_camera(t_v3f point, t_v3f cam_pos, t_rotation_data rd)
{
	return (ft_rotate_point(ft_v3f_sub(point, cam_pos), rd));
}

t_v3f	ft_rotate_point(t_v3f pos, t_rotation_data rd)
{
	t_v3f	r;
	float	px;
	float	py;
	float	py2;
	float	pz2;

	r = pos;
	px = r.x * rd.cosY - r.y * rd.sinY;
	py = r.x * rd.sinY + r.y * rd.cosY;
	r.x = px;
	r.y = py;
	py2 = r.y * rd.cosP - r.z * rd.sinP;
	pz2 = r.y * rd.sinP + r.z * rd.cosP;
	r.y = py2;
	r.z = pz2;
	return (r);
}

t_screenpoint	ft_project_point(t_v3f cameraSpace, float focal,
		float cam_inverse)
{
	t_screenpoint	sp;
	float			sx;
	float			sy;

	sp.depth = cameraSpace.y;
	if (cameraSpace.y <= 0)
		cameraSpace.y = -cameraSpace.y;
	sx = (cameraSpace.x * focal) * cam_inverse + (WIDTH_WIN / 2.0f);
	sy = (cameraSpace.z * focal) * cam_inverse + (HEIGHT_WIN / 2.0f);
	sp.x = sx;
	sp.y = sy;
	return (sp);
}
