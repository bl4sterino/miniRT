/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:45:52 by pberne            #+#    #+#             */
/*   Updated: 2026/02/25 15:17:18 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3D_H
# define V3D_H

typedef union __attribute__((aligned(16))) u_v3d
{
	struct
	{
		double		x;
		double		y;
		double		z;
	};
	double			v[3];
}					t_v3d;

static inline t_v3d	ft_v3d_add(t_v3d v1, t_v3d v2)
{
	return ((t_v3d){{v1.x + v2.x, v1.y + v2.y, v1.z + v2.z}});
}

static inline t_v3d	ft_v3d_sub(t_v3d v1, t_v3d v2)
{
	return ((t_v3d){{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z}});
}

static inline t_v3d	ft_v3d_mult(t_v3d v1, t_v3d v2)
{
	return ((t_v3d){{v1.x * v2.x, v1.y * v2.y, v1.z * v2.z}});
}

static inline t_v3d	ft_v3d_scale(t_v3d v1, double d)
{
	return ((t_v3d){{v1.x * d, v1.y * d, v1.z * d}});
}

static inline t_v3d	ft_v3d_div(t_v3d v1, double d)
{
	return (ft_v3d_scale(v1, 1.0 / d));
}

t_v3d				ft_v3d_div_safe(t_v3d v1, t_v3d v2);

#endif
