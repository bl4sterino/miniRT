/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bounds.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:26:21 by pberne            #+#    #+#             */
/*   Updated: 2026/04/01 15:46:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_BOUNDS_H
# define COLLISION_BOUNDS_H

# include "rt.h"

static inline float	ft_bounds_collision(t_ray ray, t_bounds b)
{
	t_v2f	min_max;
	float	t1;
	float	t2;

	min_max.x = (b.v[ray.inv_sign[0]].x - ray.origin.x) * ray.inv_dir.x;
	min_max.y = (b.v[1 - ray.inv_sign[0]].x - ray.origin.x) * ray.inv_dir.x;
	if (min_max.x > min_max.y)
		return (FT_INFINITY);
	t1 = (b.v[ray.inv_sign[1]].y - ray.origin.y) * ray.inv_dir.y;
	t2 = (b.v[1 - ray.inv_sign[1]].y - ray.origin.y) * ray.inv_dir.y;
	if (t1 > min_max.x)
		min_max.x = t1;
	if (t2 < min_max.y)
		min_max.y = t2;
	if (min_max.x > min_max.y)
		return (FT_INFINITY);
	t1 = (b.v[ray.inv_sign[2]].z - ray.origin.z) * ray.inv_dir.z;
	t2 = (b.v[1 - ray.inv_sign[2]].z - ray.origin.z) * ray.inv_dir.z;
	if (t1 > min_max.x)
		min_max.x = t1;
	if (t2 < min_max.y)
		min_max.y = t2;
	if (min_max.x > min_max.y || min_max.y < 0.0f)
		return (FT_INFINITY);
	return (tn_f(min_max.x > 0.0f, min_max.x, 0.0f));
}

static inline void	ft_intersect_aabb_x2_fast(t_ray ray, const t_bounds2x *b,
		float dist[2])
{
	t_v3f t1;
	t_v3f t2;
	t_v3f tmin;
	t_v3f tmax;

	t1.v = (b->min_x.v - ray.origin.x) * ray.inv_dir.x;
	t2.v = (b->max_x.v - ray.origin.x) * ray.inv_dir.x;
	tmin = ft_v3f_min(t1, t2);
	tmax = ft_v3f_max(t1, t2);
	t1.v = (b->min_y.v - ray.origin.y) * ray.inv_dir.y;
	t2.v = (b->max_y.v - ray.origin.y) * ray.inv_dir.y;
	tmin = ft_v3f_max(tmin, ft_v3f_min(t1, t2));
	tmax = ft_v3f_min(tmax, ft_v3f_max(t1, t2));
	t1.v = (b->min_z.v - ray.origin.z) * ray.inv_dir.z;
	t2.v = (b->max_z.v - ray.origin.z) * ray.inv_dir.z;
	tmin = ft_v3f_max(tmin, ft_v3f_min(t1, t2));
	tmax = ft_v3f_min(tmax, ft_v3f_max(t1, t2));
	dist[0] = tn_f(tmin.v[0] <= tmax.v[0] && tmax.v[0] > 0.0f,
			tmin.v[0], FT_INFINITY);
	dist[1] = tn_f(tmin.v[1] <= tmax.v[1] && tmax.v[1] > 0.0f,
			tmin.v[1], FT_INFINITY);
}

#endif
