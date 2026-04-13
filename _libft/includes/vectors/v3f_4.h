/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3f_4.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:47:28 by pberne            #+#    #+#             */
/*   Updated: 2026/03/06 14:34:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3F_4_H
# define V3F_4_H

# include "v3f_random.h"
# include "vectors.h"

static inline t_v3f	ft_v3f_reflect(t_v3f direction, t_v3f normal)
{
	float	float_dot;
	t_v4sf	ret;

	float_dot = 2.0f * ft_v3f_dot(direction, normal);
	ret = direction.v - normal.v * float_dot;
	return ((t_v3f){.v = ret});
}

static inline t_v3f	ft_v3f_reflect_diffuse(t_v3f direction, t_v3f normal,
		float diffusion)
{
	if (diffusion > 0.0f)
		normal = ft_v3f_add(normal, ft_v3f_scale(ft_v3f_random(), diffusion));
	return (ft_v3f_reflect(direction, normal));
}

/* rotate a vector around worldsapce x, y and z axis in this order */
static inline t_v3f	ft_v3f_rotate_worldspace(t_v3f src, t_v3f angles)
{
	src = ft_v3f_rotate_around(src, (t_v3f){{1.0f, 0.0f, 0.0f}}, angles.x);
	src = ft_v3f_rotate_around(src, (t_v3f){{0.0f, 1.0f, 0.0f}}, angles.y);
	src = ft_v3f_rotate_around(src, (t_v3f){{0.0f, 0.0f, 1.0f}}, angles.z);
	return (src);
}

static inline t_v3f	ft_v3f_refract(t_v3f i, t_v3f n, float from, float to)
{
	float	ratio;
	float	cos_i;
	float	k;
	float	sin2_t;

	ratio = from / to;
	cos_i = -ft_v3f_dot(i, n);
	sin2_t = ratio * ratio * (1.0f - cos_i * cos_i);
	if (sin2_t > 1.0f)
		return ((t_v3f){{0.0f, 0.0f, 0.0f}});
	k = cos_i * ratio - sqrtf(1.0f - sin2_t);
	return ((t_v3f){.v = i.v * ratio + n.v * k});
}

#endif
