/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_cylinder.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:35:18 by pberne            #+#    #+#             */
/*   Updated: 2026/03/20 15:10:33 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_CYLINDER_H
# define COLLISION_CYLINDER_H

# include "rt.h"

// cylinder defined by extremes a and b, and radious ra
// a position, b top_Center
static inline float	ft_disk_collision(t_ray ray, t_v3f center, t_v3f normal,
		float radius)
{
	float	denom;
	t_v3f	oc;
	float	t;
	t_v3f	hit_p;
	t_v3f	v;

	denom = ft_v3f_dot(ray.direction, normal);
	// Ray is parallel to the cap
	if (fabsf(denom) < EPSILON)
		return (FT_INFINITY);
	oc = ft_v3f_sub(center, ray.origin);
	t = ft_v3f_dot(oc, normal) / denom;
	if (t < EPSILON)
		return (FT_INFINITY);
	// Check if hit point is within the radius
	hit_p = ft_v3f_add(ray.origin, ft_v3f_scale(ray.direction, t));
	v = ft_v3f_sub(hit_p, center);
	if (ft_v3f_dot(v, v) > radius * radius)
		return (FT_INFINITY);
	return (t);
}

static inline float	ft_cylinder_collision(t_ray ray, t_cylinder cyl)
{
	float	t_min;
	t_v3f	oc;
	float	rd_dot_n;
	float	oc_dot_n;
	t_v3f	v_perp;
	t_v3f	oc_perp;
	float	a;
	float	b;
	float	c;
	float	delta;
	float	sqrt_delta;
	float ts[2];
	float	h;
	float	t_bot;
	float	t_top;

	t_min = FT_INFINITY;
	// 1. Check Tube
	oc = ft_v3f_sub(ray.origin, cyl.position);
	rd_dot_n = ft_v3f_dot(ray.direction, cyl.normal);
	oc_dot_n = ft_v3f_dot(oc, cyl.normal);
	v_perp = ft_v3f_sub(ray.direction, ft_v3f_scale(cyl.normal, rd_dot_n));
	oc_perp = ft_v3f_sub(oc, ft_v3f_scale(cyl.normal, oc_dot_n));
	a = ft_v3f_dot(v_perp, v_perp);
	b = 2.0f * ft_v3f_dot(v_perp, oc_perp);
	c = ft_v3f_dot(oc_perp, oc_perp) - (cyl.radius * cyl.radius);
	delta = b * b - 4 * a * c;
	if (delta >= 0)
	{
		sqrt_delta = sqrtf(delta);
		ts[0] = (-b - sqrt_delta) / (2.0f * a);
		ts[1] = (-b + sqrt_delta) / (2.0f * a);
		for (int i = 0; i < 2; i++)
		{
			if (ts[i] > EPSILON && ts[i] < t_min)
			{
				h = rd_dot_n * ts[i] + oc_dot_n;
				if (h >= 0 && h <= cyl.height)
					t_min = ts[i];
			}
		}
	}
	t_bot = ft_disk_collision(ray, cyl.position, cyl.normal, cyl.radius);
	if (t_bot < t_min)
		t_min = t_bot;
	t_top = ft_disk_collision(ray, cyl.top_center, cyl.normal, cyl.radius);
	if (t_top < t_min)
		t_min = t_top;
	return (t_min);
}

static inline t_v3f	ft_cylinder_normal(t_v3f hit_point, t_cylinder cyl,
		t_v3f ray_dir)
{
	t_v3f	normal;
	t_v3f	cp;
	float	dist_along_axis;
	t_v3f	projection;

	cp = ft_v3f_sub(hit_point, cyl.position);
	dist_along_axis = ft_v3f_dot(cp, cyl.normal);
	if (dist_along_axis < EPSILON)
	{
		normal = ft_v3f_scale(cyl.normal, -1.0f);
	}
	else if (dist_along_axis > cyl.height - EPSILON)
	{
		normal = cyl.normal;
	}
	else
	{
		projection = ft_v3f_add(cyl.position, ft_v3f_scale(cyl.normal,
					dist_along_axis));
		normal = ft_v3f_normalize(ft_v3f_sub(hit_point, projection));
	}
	if (ft_v3f_dot(ray_dir, normal) > 0.0f)
		normal = ft_v3f_scale(normal, -1.0f);
	return (normal);
}

#endif