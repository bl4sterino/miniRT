/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_ellipsoid.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:40:02 by pberne            #+#    #+#             */
/*   Updated: 2026/03/09 14:26:33 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISIONS_ELLIPSOID_H
# define COLLISIONS_ELLIPSOID_H

# include "rt.h"

typedef struct s_ellipsoid_collision_context
{
	t_v3f			oc;
	float			a;
	float			b;
	float			c;
	float			disc;
	float			sqrt_d;
	float			t;

}					t_ellipsoid_colision_context;

static inline float	ft_ellipsoid_collision(t_ray ray, t_ellipsoid el)
{
	t_ellipsoid_colision_context	c;

	c.oc = ft_v3f_sub(ray.origin, el.position);
	c.a = (ray.direction.x * ray.direction.x * el.inv_r2.x) + (ray.direction.y
			* ray.direction.y * el.inv_r2.y) + (ray.direction.z
			* ray.direction.z * el.inv_r2.z);
	c.b = 2.0f * ((c.oc.x * ray.direction.x * el.inv_r2.x) + (c.oc.y
				* ray.direction.y * el.inv_r2.y) + (c.oc.z * ray.direction.z
				* el.inv_r2.z));
	c.c = ((c.oc.x * c.oc.x * el.inv_r2.x) + (c.oc.y * c.oc.y * el.inv_r2.y)
			+ (c.oc.z * c.oc.z * el.inv_r2.z)) - 1.0f;
	c.disc = (c.b * c.b) - (4.0f * c.a * c.c);
	if (c.disc < 0.0f)
		return (FT_INFINITY);
	c.sqrt_d = sqrtf(c.disc);
	c.t = (-c.b - c.sqrt_d) / (2.0f * c.a);
	if (c.t < EPSILON)
		c.t = (-c.b + c.sqrt_d) / (2.0f * c.a);
	if (c.t < EPSILON)
		return (FT_INFINITY);
	return (c.t);
}

#endif