/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bounds.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:26:21 by pberne            #+#    #+#             */
/*   Updated: 2026/03/09 11:28:14 by pberne           ###   ########.fr       */
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

static inline void	ft_setup_aabb_x2(t_aabb_x2 *c, const t_bounds *b1,
		const t_bounds *b2)
{
	c->b_min_x = (t_v3f){{b1->min.x, b2->min.x, 0, 0}};
	c->b_max_x = (t_v3f){{b1->max.x, b2->max.x, 0, 0}};
	c->b_min_y = (t_v3f){{b1->min.y, b2->min.y, 0, 0}};
	c->b_max_y = (t_v3f){{b1->max.y, b2->max.y, 0, 0}};
	c->b_min_z = (t_v3f){{b1->min.z, b2->min.z, 0, 0}};
	c->b_max_z = (t_v3f){{b1->max.z, b2->max.z, 0, 0}};
}

static inline void	ft_intersect_aabb_x2_fast(t_aabb_x2 c, const t_bounds *b1,
		const t_bounds *b2, float dist[2])
{
	ft_setup_aabb_x2(&c, b1, b2);
	c.t1 = ft_v3f_mult(ft_v3f_sub(c.b_min_x, c.r_org[0]), c.r_inv[0]);
	c.t2 = ft_v3f_mult(ft_v3f_sub(c.b_max_x, c.r_org[0]), c.r_inv[0]);
	c.tmin = ft_v3f_min(c.t1, c.t2);
	c.tmax = ft_v3f_max(c.t1, c.t2);
	c.t1 = ft_v3f_mult(ft_v3f_sub(c.b_min_y, c.r_org[1]), c.r_inv[1]);
	c.t2 = ft_v3f_mult(ft_v3f_sub(c.b_max_y, c.r_org[1]), c.r_inv[1]);
	c.tmin = ft_v3f_max(c.tmin, ft_v3f_min(c.t1, c.t2));
	c.tmax = ft_v3f_min(c.tmax, ft_v3f_max(c.t1, c.t2));
	c.t1 = ft_v3f_mult(ft_v3f_sub(c.b_min_z, c.r_org[2]), c.r_inv[2]);
	c.t2 = ft_v3f_mult(ft_v3f_sub(c.b_max_z, c.r_org[2]), c.r_inv[2]);
	c.tmin = ft_v3f_max(c.tmin, ft_v3f_min(c.t1, c.t2));
	c.tmax = ft_v3f_min(c.tmax, ft_v3f_max(c.t1, c.t2));
	dist[0] = tn_f(c.tmin.v[0] <= c.tmax.v[0] && c.tmax.v[0] > 0.0f,
			c.tmin.v[0], FT_INFINITY);
	dist[1] = tn_f(c.tmin.v[1] <= c.tmax.v[1] && c.tmax.v[1] > 0.0f,
			c.tmin.v[1], FT_INFINITY);
}

#endif
