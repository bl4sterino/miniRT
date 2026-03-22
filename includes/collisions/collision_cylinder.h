/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_cylinder.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:35:18 by pberne            #+#    #+#             */
/*   Updated: 2026/03/22 11:29:04 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_CYLINDER_H
# define COLLISION_CYLINDER_H

# include "rt.h"

static inline float	ft_disk_collision(t_ray ray, t_v3f center, t_v3f normal,
		float radius)
{
	float	denom;
	t_v3f	oc;
	float	t;
	t_v3f	hit_p;
	t_v3f	v;

	denom = ft_v3f_dot(ray.direction, normal);
	if (fabsf(denom) < EPSILON)
		return (FT_INFINITY);
	oc = ft_v3f_sub(center, ray.origin);
	t = ft_v3f_dot(oc, normal) / denom;
	if (t < EPSILON)
		return (FT_INFINITY);
	hit_p = ft_v3f_add(ray.origin, ft_v3f_scale(ray.direction, t));
	v = ft_v3f_sub(hit_p, center);
	if (ft_v3f_dot(v, v) > radius * radius)
		return (FT_INFINITY);
	return (t);
}

typedef struct s_cyl_collision_data
{
	float			t_min;
	t_v3f			oc;
	float			rd_dot_n;
	float			oc_dot_n;
	t_v3f			v_perp;
	t_v3f			oc_perp;
	float			a;
	float			b;
	float			c;
	float			delta;
	float			sqrt_delta;
	float			ts[2];
	float			h;
	float			t_bot;
	float			t_top;
}					t_cyl_collision_data;

static inline void	ft_cyl_side_colision(t_cylinder cyl,
		t_cyl_collision_data *c)
{
	c->sqrt_delta = sqrtf(c->delta);
	c->ts[0] = (-c->b - c->sqrt_delta) / (2.0f * c->a);
	c->ts[1] = (-c->b + c->sqrt_delta) / (2.0f * c->a);
	for (int i = 0; i < 2; i++)
	{
		if (c->ts[i] > EPSILON && c->ts[i] < c->t_min)
		{
			c->h = c->rd_dot_n * c->ts[i] + c->oc_dot_n;
			if (c->h >= 0 && c->h <= cyl.height)
				c->t_min = c->ts[i];
		}
	}
}

static inline float	ft_cylinder_collision(t_ray ray, t_cylinder cyl)
{
	t_cyl_collision_data	c;

	c.t_min = FT_INFINITY;
	c.oc = ft_v3f_sub(ray.origin, cyl.position);
	c.rd_dot_n = ft_v3f_dot(ray.direction, cyl.normal);
	c.oc_dot_n = ft_v3f_dot(c.oc, cyl.normal);
	c.v_perp = ft_v3f_sub(ray.direction, ft_v3f_scale(cyl.normal, c.rd_dot_n));
	c.oc_perp = ft_v3f_sub(c.oc, ft_v3f_scale(cyl.normal, c.oc_dot_n));
	c.a = ft_v3f_dot(c.v_perp, c.v_perp);
	c.b = 2.0f * ft_v3f_dot(c.v_perp, c.oc_perp);
	c.c = ft_v3f_dot(c.oc_perp, c.oc_perp) - (cyl.radius * cyl.radius);
	c.delta = c.b * c.b - 4 * c.a * c.c;
	if (c.delta >= 0)
		ft_cyl_side_colision(cyl, &c);
	c.t_bot = ft_disk_collision(ray, cyl.position, cyl.normal, cyl.radius);
	if (c.t_bot < c.t_min)
		c.t_min = c.t_bot;
	c.t_top = ft_disk_collision(ray, cyl.top_center, cyl.normal, cyl.radius);
	if (c.t_top < c.t_min)
		c.t_min = c.t_top;
	return (c.t_min);
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
		normal = ft_v3f_scale(cyl.normal, -1.0f);
	else if (dist_along_axis > cyl.height - EPSILON)
		normal = cyl.normal;
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