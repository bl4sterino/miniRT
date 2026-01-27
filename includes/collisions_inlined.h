/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_inlined.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:00:06 by pberne            #+#    #+#             */
/*   Updated: 2026/01/27 13:01:04 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISIONS_INLINED_H
# define COLLISIONS_INLINED_H

# include "rt.h"

static inline double	ft_bounds_collision(t_ray ray, t_bounds b)
{
	t_v2d	min_max;
	double	t1;
	double	t2;

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
	if (min_max.x > min_max.y || min_max.y < 0.0)
		return (INFINITY);
	return (tn_d(min_max.x > 0.0, min_max.x, 0.0));
}

static inline double	ft_sphere_collision(t_ray ray, t_sphere sphere)
{
	t_v3d	oc;
	double	a;
	double	b;
	double	discriminant;
	double	t;

	oc = ft_v3d_sub(ray.origin, sphere.position);
	a = ft_v3d_dot(ray.direction, ray.direction);
	b = 2.0 * ft_v3d_dot(ray.direction, oc);
	discriminant = (b * b) - (4 * a * (ft_v3d_dot(oc, oc) - (sphere.radius
					* sphere.radius)));
	if (discriminant < 0)
		return (INFINITY);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t < 0)
		t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t < 0)
		return (INFINITY);
	return (t);
}

#endif