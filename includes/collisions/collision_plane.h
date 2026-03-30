/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_plane.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:34:53 by pberne            #+#    #+#             */
/*   Updated: 2026/03/30 11:11:28 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_PLANE_H
# define COLLISION_PLANE_H

# include "rt.h"

static inline float	ft_plane_collision(t_ray ray, t_plane plane)
{
	float	denom;
	float	t;
	t_v3f	oc;

	denom = ft_v3f_dot(plane.normal, ray.direction);
	if (fabsf(denom) < EPSILON)
		return (FT_INFINITY);
	oc = ft_v3f_sub(plane.position, ray.origin);
	t = ft_v3f_dot(oc, plane.normal) / denom;
	if (t < 0.0f)
		return (FT_INFINITY);
	return (t);
}

#endif
