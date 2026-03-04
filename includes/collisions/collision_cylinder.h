/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_cylinder.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:35:18 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 17:23:17 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_CYLINDER_H
# define COLLISION_CYLINDER_H

# include "rt.h"

typedef struct s_cylinder_collision_context
{
	t_v3f			oc;
	float			radius;
	float			min_t;
	float			rd_dot_n;
	float			oc_dot_n;
	t_v3f			a_vec;
	t_v3f			c_vec;
	float			a;
	float			b;
	float			c;
	float			disc;
	float			sqrt_d;
	float			t;
	float			hit_height;
}					t_cylinder_collision_context;

typedef struct s_cylinder_caps_context
{
	float			cap_t;
	t_v3f			caps[2];
	float			denom;
	t_v3f			p;
	t_v3f			v;
	int				i;
}					t_cylinder_caps_context;

static inline void	ft_cyl_caps_intersection(t_cylinder_collision_context *c,
		t_cylinder cyl, t_ray ray)
{
	t_cylinder_caps_context	caps_c;

	caps_c.i = -1;
	caps_c.caps[0] = cyl.position;
	caps_c.caps[1] = ft_v3f_add(cyl.position, ft_v3f_scale(cyl.normal,
				cyl.height));
	while (++caps_c.i < 2)
	{
		caps_c.denom = ft_v3f_dot(ray.direction, cyl.normal);
		if (fabsf(caps_c.denom) > EPSILON)
		{
			caps_c.cap_t = ft_v3f_dot(ft_v3f_sub(caps_c.caps[caps_c.i],
						ray.origin), cyl.normal) / caps_c.denom;
			if (caps_c.cap_t > EPSILON && caps_c.cap_t < c->min_t)
			{
				caps_c.p = ft_v3f_add(ray.origin, ft_v3f_scale(ray.direction,
							caps_c.cap_t));
				caps_c.v = ft_v3f_sub(caps_c.p, caps_c.caps[caps_c.i]);
				if (ft_v3f_dot(caps_c.v, caps_c.v) <= (c->radius * c->radius))
					c->min_t = caps_c.cap_t;
			}
		}
	}
}

static inline void	ft_cyl_intersect(t_cylinder_collision_context *c,
		t_cylinder cyl)
{
	if (c->disc >= 0.0f)
	{
		c->sqrt_d = sqrtf(c->disc);
		c->t = (-c->b - c->sqrt_d) / (2.0f * c->a);
		if (c->t > EPSILON && c->t < c->min_t)
		{
			c->hit_height = c->rd_dot_n * c->t + c->oc_dot_n;
			if (c->hit_height >= 0 && c->hit_height <= cyl.height)
				c->min_t = c->t;
		}
		c->t = (-c->b + c->sqrt_d) / (2.0f * c->a);
		if (c->t > EPSILON && c->t < c->min_t)
		{
			c->hit_height = c->rd_dot_n * c->t + c->oc_dot_n;
			if (c->hit_height >= 0 && c->hit_height <= cyl.height)
				c->min_t = c->t;
		}
	}
}

static inline float	ft_cylinder_collision(t_ray ray, t_cylinder cyl)
{
	t_cylinder_collision_context	c;

	c.oc = ft_v3f_sub(ray.origin, cyl.position);
	c.radius = cyl.diameter / 2.0f;
	c.min_t = INFINITY;
	c.rd_dot_n = ft_v3f_dot(ray.direction, cyl.normal);
	c.oc_dot_n = ft_v3f_dot(c.oc, cyl.normal);
	c.a_vec = ft_v3f_sub(ray.direction, ft_v3f_scale(cyl.normal, c.rd_dot_n));
	c.c_vec = ft_v3f_sub(c.oc, ft_v3f_scale(cyl.normal, c.oc_dot_n));
	c.a = ft_v3f_dot(c.a_vec, c.a_vec);
	c.b = 2.0f * ft_v3f_dot(c.a_vec, c.c_vec);
	c.c = ft_v3f_dot(c.c_vec, c.c_vec) - (c.radius * c.radius);
	c.disc = (c.b * c.b) - (4.0f * c.a * c.c);
	ft_cyl_intersect(&c, cyl);
	ft_cyl_caps_intersection(&c, cyl, ray);
	return (c.min_t);
}

static inline t_v3f	ft_cylinder_normal(t_v3f hit_point, t_cylinder cyl,
		t_v3f ray_dir)
{
	t_v3f	v;
	float	dist;
	t_v3f	normal;
	t_v3f	projection;

	v = ft_v3f_sub(hit_point, cyl.position);
	dist = ft_v3f_dot(v, cyl.normal);
	if (dist >= cyl.height - EPSILON)
		normal = cyl.normal;
	else if (dist <= EPSILON)
		normal = ft_v3f_scale(cyl.normal, -1.0f);
	else
	{
		projection = ft_v3f_scale(cyl.normal, dist);
		normal = ft_v3f_normalize(ft_v3f_sub(v, projection));
	}
	if (ft_v3f_dot(ray_dir, normal) > 0.0f)
		normal = ft_v3f_scale(normal, -1.0f);
	return (normal);
}

#endif