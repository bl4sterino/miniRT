/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions_inlined.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:00:06 by pberne            #+#    #+#             */
/*   Updated: 2026/01/29 16:23:21 by pberne           ###   ########.fr       */
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

static inline double	ft_plane_collision(t_ray ray, t_plane plane)
{
	double	denom;
	double	t;
	t_v3d	oc;

	denom = ft_v3d_dot(plane.normal, ray.direction);
	if (fabs(denom) < EPSILON)
		return (INFINITY);
	oc = ft_v3d_sub(plane.position, ray.origin);
	t = ft_v3d_dot(oc, plane.normal) / denom;
	if (t < 0)
		return (INFINITY);
	return (t);
}

/* This one is Gemini's, didin't look into it but it just works™  */
static inline double    ft_cylinder_collision(t_ray ray, t_cylinder cyl)
{
    t_v3d   oc;
    double  a, b, c, disc, t0, t1, h, r;
    t_v3d   q;
    r = cyl.diameter / 2.0;

    oc = ft_v3d_sub(ray.origin, cyl.position);
    
    a = 1.0 - 
        pow(ft_v3d_dot(ray.direction, cyl.normal), 2);
    b = 2 * (ft_v3d_dot(ray.direction, oc) - 
        (ft_v3d_dot(ray.direction, cyl.normal) * ft_v3d_dot(oc, cyl.normal)));
    c = ft_v3d_dot(oc, oc) - 
        pow(ft_v3d_dot(oc, cyl.normal), 2) - (r * r);

    disc = (b * b) - (4 * a * c);
    if (disc < 0)
        return (INFINITY);

    t0 = (-b - sqrt(disc)) / (2.0 * a);
    t1 = (-b + sqrt(disc)) / (2.0 * a);

    double t_hit = INFINITY;
    double half_h = cyl.height / 2.0;
    if (t0 > 0)
    {
        q = ft_v3d_add(ray.origin, ft_v3d_scale(ray.direction, t0));
        h = ft_v3d_dot(ft_v3d_sub(q, cyl.position), cyl.normal);
        if (h >= -half_h && h <= half_h)
            t_hit = t0;
    }
    if (t_hit == INFINITY && t1 > 0)
    {
        q = ft_v3d_add(ray.origin, ft_v3d_scale(ray.direction, t1));
        h = ft_v3d_dot(ft_v3d_sub(q, cyl.position), cyl.normal);
        if (h >= -half_h && h <= half_h)
            t_hit = t1;
    }
    return (t_hit);
}

#endif