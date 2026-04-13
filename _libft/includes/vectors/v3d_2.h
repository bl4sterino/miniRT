/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_2.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:45:52 by pberne            #+#    #+#             */
/*   Updated: 2026/02/17 12:19:54 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3D_2_H
# define V3D_2_H

# include "v3d.h"

static inline double	ft_v3d_dot(t_v3d v1, t_v3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

static inline t_v3d	ft_v3d_cross(t_v3d v1, t_v3d v2)
{
	return ((t_v3d){{v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x
			* v2.y - v1.y * v2.x}});
}

static inline double	ft_v3d_length_squared(t_v3d v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

static inline double	ft_v3d_length(t_v3d v)
{
	return (sqrt(ft_v3d_length_squared(v)));
}

static inline t_v3d	ft_v3d_normalize(t_v3d v)
{
	return (ft_v3d_scale(v, 1.0 / ft_v3d_length(v)));
}

#endif
