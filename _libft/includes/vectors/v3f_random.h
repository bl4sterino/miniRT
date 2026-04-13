/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3f_random.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:39:33 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 15:51:11 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3F_RANDOM_H
# define V3F_RANDOM_H

# include "vectors.h"

static inline t_v3f	ft_v3f_random(void)
{
	t_v3f	res;
	float	x;
	float	y;
	float	s;
	float	multiplier;

	x = fast_rand() * 2.0f - 1.0f;
	y = fast_rand() * 2.0f - 1.0f;
	s = x * x + y * y;
	while (s >= 1.0f)
	{
		x = fast_rand() * 2.0f - 1.0f;
		y = fast_rand() * 2.0f - 1.0f;
		s = x * x + y * y;
	}
	multiplier = 2.0f * sqrtf(1.0f - s);
	res.x = x * multiplier;
	res.y = y * multiplier;
	res.z = 1.0f - 2.0f * s;
	return (res);
}

static inline t_v3f	ft_v3f_random_hem(t_v3f normal)
{
	t_v3f	in_unit_sphere;

	in_unit_sphere = ft_v3f_random();
	if (ft_v3f_dot(in_unit_sphere, normal) > 0.0f)
		return (in_unit_sphere);
	else
		return (ft_v3f_scale(in_unit_sphere, -1.0f));
}

static inline t_v3f	ft_v3f_random_hemisphere(t_v3f normal)
{
	t_v3f	in_unit_sphere;

	in_unit_sphere = ft_v3f_random();
	if (ft_v3f_dot(in_unit_sphere, normal) > 0.0f)
		return (in_unit_sphere);
	else
		return (ft_v3f_scale(in_unit_sphere, -1.0f));
}

static inline t_v3f	ft_random_disk(void)
{
	float	x;
	float	y;

	x = fast_rand() * 2.0f - 1.0f;
	y = fast_rand() * 2.0f - 1.0f;
	while (x * x + y * y >= 1.0f)
	{
		x = fast_rand() * 2.0f - 1.0f;
		y = fast_rand() * 2.0f - 1.0f;
	}
	return (v3f(x, y, 0));
}

#endif