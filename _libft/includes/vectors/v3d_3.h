/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_3.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:35:27 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 17:39:07 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3D_3_H
# define V3D_3_H

# include "v3d.h"
# include <math.h>

static inline t_v3d	ft_v3d_min(t_v3d a, t_v3d b)
{
	return ((t_v3d){{fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z)}});
}

static inline t_v3d	ft_v3d_max(t_v3d a, t_v3d b)
{
	return ((t_v3d){{fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z)}});
}

static inline t_v3d	ft_v3d_lerp(t_v3d a, t_v3d b, double t)
{
	t = ft_clampd(t, 0.0, 1.0);
	return (ft_v3d_add(ft_v3d_scale(a, 1.0 - t), ft_v3d_scale(b, t)));
}

/// rotates a vector around an axis, angle is in degrees
static inline t_v3d	ft_v3d_rotate_around(t_v3d vector, t_v3d axis, double angle)
{
	t_v3d	k;
	double	cos_a;
	double	sin_a;
	t_v3d	term;

	angle *= DEG2RAD;
	k = ft_v3d_normalize(axis);
	cos_a = cos(angle);
	sin_a = sin(angle);
	term = ft_v3d_scale(vector, cos_a);
	term = ft_v3d_add(term, ft_v3d_scale(ft_v3d_cross(k, vector), sin_a));
	term = ft_v3d_add(term, ft_v3d_scale(k, ft_v3d_dot(k, vector) * (1.0
					- cos_a)));
	return (term);
}

#endif