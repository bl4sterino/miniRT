/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3f_3.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:06:28 by pberne            #+#    #+#             */
/*   Updated: 2026/03/30 15:39:31 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3F_3_H
# define V3F_3_H

# include "libft.h"
# include "v3f.h"

// static inline t_v3f	ft_v3f_min(t_v3f a, t_v3f b)
// {
// 	return ((t_v3f){{fminf(a.x, b.x), fminf(a.y, b.y), fminf(a.z, b.z)}});
// }

// static inline t_v3f	ft_v3f_max(t_v3f a, t_v3f b)
// {
// 	return ((t_v3f){{fmaxf(a.x, b.x), fmaxf(a.y, b.y), fmaxf(a.z, b.z)}});
// }

static inline t_v3f	ft_v3f_min(t_v3f a, t_v3f b)
{
	return ((t_v3f){.v = __builtin_ia32_minps(a.v, b.v)});
}

static inline t_v3f	ft_v3f_max(t_v3f a, t_v3f b)
{
	return ((t_v3f){.v = __builtin_ia32_maxps(a.v, b.v)});
}

static inline t_v3f	ft_v3f_lerp(t_v3f a, t_v3f b, float t)
{
	t = ft_clampf(t, 0.0f, 1.0f);
	return ((t_v3f){.v = a.v + (b.v - a.v) * t});
}

/// rotates a vector around an axis, angle is in degrees
static inline t_v3f	ft_v3f_rotate_around(t_v3f vector, t_v3f axis, float angle)
{
	t_v3f	k;
	float	cos_a;
	float	sin_a;
	t_v3f	term;

	angle *= DEG2RAD;
	k = ft_v3f_normalize(axis);
	cos_a = cosf(angle);
	sin_a = sinf(angle);
	term = ft_v3f_scale(vector, cos_a);
	term = ft_v3f_add(term, ft_v3f_scale(ft_v3f_cross(k, vector), sin_a));
	term = ft_v3f_add(term, ft_v3f_scale(k, ft_v3f_dot(k, vector) * (1.0f
					- cos_a)));
	return (term);
}

#endif