/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_sphere.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:30:12 by pberne            #+#    #+#             */
/*   Updated: 2026/03/09 14:25:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef struct s_sphere_context
{
	t_v3f			oc;
	float			a;
	float			b;
	float			discriminant;
	float			t;
	float			sqrt_d;
}					t_sphere_context;

static inline float	ft_sphere_collision(t_ray ray, t_sphere sphere)
{
	t_sphere_context	c;

	c.oc = ft_v3f_sub(ray.origin, sphere.position);
	c.a = ft_v3f_dot(ray.direction, ray.direction);
	c.b = 2.0f * ft_v3f_dot(ray.direction, c.oc);
	c.discriminant = (c.b * c.b) - (4.0f * c.a * (ft_v3f_dot(c.oc, c.oc)
				- (sphere.radius * sphere.radius)));
	if (c.discriminant < 0.0f)
		return (INFINITY);
	c.sqrt_d = sqrtf(c.discriminant);
	c.t = (-c.b - c.sqrt_d) / (2.0f * c.a);
	if (c.t < EPSILON)
		c.t = (-c.b + c.sqrt_d) / (2.0f * c.a);
	if (c.t < EPSILON)
		return (INFINITY);
	return (c.t);
}
