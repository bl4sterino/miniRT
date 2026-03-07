/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bounds.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 11:26:21 by pberne            #+#    #+#             */
/*   Updated: 2026/03/07 16:22:32 by pberne           ###   ########.fr       */
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
		return (INFINITY);
	t1 = (b.v[ray.inv_sign[1]].y - ray.origin.y) * ray.inv_dir.y;
	t2 = (b.v[1 - ray.inv_sign[1]].y - ray.origin.y) * ray.inv_dir.y;
	if (t1 > min_max.x)
		min_max.x = t1;
	if (t2 < min_max.y)
		min_max.y = t2;
	if (min_max.x > min_max.y)
		return (INFINITY);
	t1 = (b.v[ray.inv_sign[2]].z - ray.origin.z) * ray.inv_dir.z;
	t2 = (b.v[1 - ray.inv_sign[2]].z - ray.origin.z) * ray.inv_dir.z;
	if (t1 > min_max.x)
		min_max.x = t1;
	if (t2 < min_max.y)
		min_max.y = t2;
	if (min_max.x > min_max.y || min_max.y < 0.0f)
		return (INFINITY);
	return (tn_f(min_max.x > 0.0f, min_max.x, 0.0f));
}

/// 
static inline t_bounds_4x	ft_get_bounds_4x(const t_bounds *b1,
		const t_bounds *b2, const t_bounds *b3, const t_bounds *b4)
{
	t_bounds_4x	b;

	b.b_min_x = (t_v3f){{b1->min.x, b2->min.x, b3->min.x, b4->min.x}};
	b.b_max_x = (t_v3f){{b1->max.x, b2->max.x, b3->max.x, b4->max.x}};
	b.b_min_y = (t_v3f){{b1->min.y, b2->min.y, b3->min.y, b4->min.y}};
	b.b_max_y = (t_v3f){{b1->max.y, b2->max.y, b3->max.y, b4->max.y}};
	b.b_min_z = (t_v3f){{b1->min.z, b2->min.z, b3->min.z, b4->min.z}};
	b.b_max_z = (t_v3f){{b1->max.z, b2->max.z, b3->max.z, b4->max.z}};
	return (b);
}

// static inline void	ft_intersect_aabb_x2_fast(t_aabb_x2 c,
		// const t_bounds *b1,
// 		const t_bounds *b2, float dist[2])
// {
// 	float	res_min[4];
// 	float	res_max[4];

// 	ft_setup_aabb_x2(&c, b1, b2);
// 	c.t1 = _mm_mul_ps(_mm_sub_ps(c.b_min_x, c.r_org[0]), c.r_inv[0]);
// 	c.t2 = _mm_mul_ps(_mm_sub_ps(c.b_max_x, c.r_org[0]), c.r_inv[0]);
// 	c.tmin = _mm_min_ps(c.t1, c.t2);
// 	c.tmax = _mm_max_ps(c.t1, c.t2);
// 	c.t1 = _mm_mul_ps(_mm_sub_ps(c.b_min_y, c.r_org[1]), c.r_inv[1]);
// 	c.t2 = _mm_mul_ps(_mm_sub_ps(c.b_max_y, c.r_org[1]), c.r_inv[1]);
// 	c.tmin = _mm_max_ps(c.tmin, _mm_min_ps(c.t1, c.t2));
// 	c.tmax = _mm_min_ps(c.tmax, _mm_max_ps(c.t1, c.t2));
// 	c.t1 = _mm_mul_ps(_mm_sub_ps(c.b_min_z, c.r_org[2]), c.r_inv[2]);
// 	c.t2 = _mm_mul_ps(_mm_sub_ps(c.b_max_z, c.r_org[2]), c.r_inv[2]);
// 	c.tmin = _mm_max_ps(c.tmin, _mm_min_ps(c.t1, c.t2));
// 	c.tmax = _mm_min_ps(c.tmax, _mm_max_ps(c.t1, c.t2));
// 	_mm_store_ps(res_min, c.tmin);
// 	_mm_store_ps(res_max, c.tmax);
// 	dist[0] = tn_f(res_min[0] <= res_max[0] && res_max[0] > 0.0f, res_min[0],
// 			INFINITY);
// 	dist[1] = tn_f(res_min[1] <= res_max[1] && res_max[1] > 0.0f, res_min[1],
// 			INFINITY);
// }

static inline void	ft_intersect_aabb_x4(t_aabb_4x c, t_bounds_4x *bounds_4x,
	t_v3f *dist)
{
	c.t1 = ft_v3f_mult(ft_v3f_sub(bounds_4x->b_min_x, c.r_org[0]), c.r_inv[0]);
	c.t2 = ft_v3f_mult(ft_v3f_sub(bounds_4x->b_max_x, c.r_org[0]), c.r_inv[0]);
	c.tmin = ft_v3f_min(c.t1, c.t2);
	c.tmax = ft_v3f_max(c.t1, c.t2);
	c.t1 = ft_v3f_mult(ft_v3f_sub(bounds_4x->b_min_y, c.r_org[1]), c.r_inv[1]);
	c.t2 = ft_v3f_mult(ft_v3f_sub(bounds_4x->b_max_y, c.r_org[1]), c.r_inv[1]);
	c.tmin = ft_v3f_max(c.tmin, ft_v3f_min(c.t1, c.t2));
	c.tmax = ft_v3f_min(c.tmax, ft_v3f_max(c.t1, c.t2));
	c.t1 = ft_v3f_mult(ft_v3f_sub(bounds_4x->b_min_z, c.r_org[2]), c.r_inv[2]);
	c.t2 = ft_v3f_mult(ft_v3f_sub(bounds_4x->b_max_z, c.r_org[2]), c.r_inv[2]);
	c.tmin = ft_v3f_max(c.tmin, ft_v3f_min(c.t1, c.t2));
	c.tmax = ft_v3f_min(c.tmax, ft_v3f_max(c.t1, c.t2));
	dist->x = tn_f(c.tmin.x <= c.tmax.x && c.tmax.x > 0.0f, c.tmin.x, INFINITY);
	dist->y = tn_f(c.tmin.y <= c.tmax.y && c.tmax.y > 0.0f, c.tmin.y, INFINITY);
	dist->z = tn_f(c.tmin.z <= c.tmax.z && c.tmax.z > 0.0f, c.tmin.z, INFINITY);
	dist->w = tn_f(c.tmin.w <= c.tmax.w && c.tmax.w > 0.0f, c.tmin.w, INFINITY);
}

#endif
