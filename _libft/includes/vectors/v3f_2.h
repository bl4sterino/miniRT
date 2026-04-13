/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3f_2.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:45:52 by pberne            #+#    #+#             */
/*   Updated: 2026/03/30 15:21:27 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3F_2_H
# define V3F_2_H

# include "v3f.h"

static inline float	ft_v3f_dot(t_v3f v1, t_v3f v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

static inline t_v3f	ft_v3f_cross(t_v3f v1, t_v3f v2)
{
	return ((t_v3f){{v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x
			* v2.y - v1.y * v2.x}});
}

static inline float	ft_v3f_length_squared(t_v3f v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

static inline float	ft_v3f_length(t_v3f v)
{
	return (sqrtf(ft_v3f_length_squared(v)));
}

static inline t_v3f	ft_v3f_normalize(t_v3f v)
{
	return (ft_v3f_scale(v, 1.0f / ft_v3f_length(v)));
}

#endif
