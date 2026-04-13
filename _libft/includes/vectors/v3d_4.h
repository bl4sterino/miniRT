/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_4.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:25:57 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 17:38:57 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3D_4_H
# define V3D_4_H

# include "v3d.h"
# include <math.h>

static inline t_v3d	ft_v3d_random(void)
{
	t_v3d	res;
	double	x;
	double	y;
	double	s;
	double	multiplier;

	x = fast_rand() * 2.0 - 1.0;
	y = fast_rand() * 2.0 - 1.0;
	s = x * x + y * y;
	while (s >= 1.0)
	{
		x = fast_rand() * 2.0 - 1.0;
		y = fast_rand() * 2.0 - 1.0;
		s = x * x + y * y;
	}
	multiplier = 2.0 * sqrt(1.0 - s);
	res.x = x * multiplier;
	res.y = y * multiplier;
	res.z = 1.0 - 2.0 * s;
	return (res);
}

static inline t_v3d	ft_v3d_random_hemisphere(t_v3d normal)
{
	t_v3d	in_unit_sphere;

	in_unit_sphere = ft_v3d_random();
	if (ft_v3d_dot(in_unit_sphere, normal) > 0.0)
		return (in_unit_sphere);
	else
		return (ft_v3d_scale(in_unit_sphere, -1.0));
}

static inline t_v3d	ft_v3d_reflect(t_v3d direction, t_v3d normal)
{
	float	double_dot;

	double_dot = 2.0f * (direction.x * normal.x + direction.y * normal.y
			+ direction.z * normal.z);
	return ((t_v3d){{direction.x - (double_dot * normal.x), direction.y
			- (double_dot * normal.y),
			direction.z - (double_dot * normal.z)}});
}

static inline t_v3d	ft_v3d_reflect_diffuse(t_v3d direction, t_v3d normal,
		double diffusion)
{
	float	double_dot;

	if (diffusion > 0)
		normal = ft_v3d_add(normal, ft_v3d_scale(ft_v3d_random(), diffusion));
	double_dot = 2.0f * (direction.x * normal.x + direction.y * normal.y
			+ direction.z * normal.z);
	return ((t_v3d){{direction.x - (double_dot * normal.x), direction.y
			- (double_dot * normal.y), direction.z - (double_dot * normal.z)}});
}

/* rotate a vector around worldsapce x, y and z axis in this order */
static inline t_v3d	ft_v3d_rotate_worldspace(t_v3d src, t_v3d angles)
{
	src = ft_v3d_rotate_around(src, (t_v3d){{1, 0, 0}}, angles.x);
	src = ft_v3d_rotate_around(src, (t_v3d){{0, 1, 0}}, angles.y);
	src = ft_v3d_rotate_around(src, (t_v3d){{0, 0, 1}}, angles.z);
	return (src);
}

#endif
