/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_bounds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:09:03 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 14:19:45 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_bounds ft_get_minimum_bounds(t_bounds bounds)
{
    if (fabsf(bounds.max.x - bounds.min.x) < EPSILON)
    {
        bounds.min.x -= EPSILON;
        bounds.max.x += EPSILON;
    }
    if (fabsf(bounds.max.y - bounds.min.y) < EPSILON)
    {
        bounds.min.y -= EPSILON;
        bounds.max.y += EPSILON;
    }
    if (fabsf(bounds.max.z - bounds.min.z) < EPSILON)
    {
        bounds.min.z -= EPSILON;
        bounds.max.z += EPSILON;
    }
    return (bounds);
}

t_bounds	ft_get_sphere_bounds(t_sphere sphere)
{
	t_v3f		v_radius;
	t_bounds	bounds;

	v_radius = (t_v3f){{sphere.radius, sphere.radius, sphere.radius}};
	bounds.min = ft_v3f_sub(sphere.position, v_radius);
	bounds.max = ft_v3f_add(sphere.position, v_radius);
	return (bounds);
}

t_bounds ft_get_cylinder_bounds(t_cylinder cyl)
{
    t_bounds    bounds;
    t_v3f       p1;
    t_v3f       p2;
    t_v3f       extents;
    float       r;

    r = cyl.diameter / 2.0f;
    // Cap 1 (Base)
    p1 = cyl.position;
    // Cap 2 (Top)
    p2 = ft_v3f_add(cyl.position, ft_v3f_scale(cyl.normal, cyl.height));

    // The "extent" is how much the radius stretches the box in each axis.
    // We use: radius * sqrt(1 - normal_component^2)
    extents.x = r * sqrtf(1.0f - cyl.normal.x * cyl.normal.x);
    extents.y = r * sqrtf(1.0f - cyl.normal.y * cyl.normal.y);
    extents.z = r * sqrtf(1.0f - cyl.normal.z * cyl.normal.z);

    // Find the min/max of the two caps, then expand by the calculated radial extent
    bounds.min.x = fminf(p1.x, p2.x) - extents.x;
    bounds.min.y = fminf(p1.y, p2.y) - extents.y;
    bounds.min.z = fminf(p1.z, p2.z) - extents.z;

    bounds.max.x = fmaxf(p1.x, p2.x) + extents.x;
    bounds.max.y = fmaxf(p1.y, p2.y) + extents.y;
    bounds.max.z = fmaxf(p1.z, p2.z) + extents.z;

    return (bounds);
}

t_bounds    ft_get_quad_bounds(t_quad quad)
{
    t_bounds    bounds;
    t_v3f       corners[4];
    t_v3f       half_w;
    t_v3f       half_h;
    int         i;


    half_w = ft_v3f_scale(quad.u_axis, quad.size.x / 2.0f);
    half_h = ft_v3f_scale(quad.v_axis, quad.size.y / 2.0f);


    corners[0] = ft_v3f_add(quad.position, ft_v3f_add(half_w, half_h));
    corners[1] = ft_v3f_add(quad.position, ft_v3f_sub(half_w, half_h));
    corners[2] = ft_v3f_sub(quad.position, ft_v3f_sub(half_w, half_h));
    corners[3] = ft_v3f_sub(quad.position, ft_v3f_add(half_w, half_h));

    bounds.min = corners[0];
    bounds.max = corners[0];

    i = 1;
    while (i < 4)
    {
        bounds.min.x = fmin(bounds.min.x, corners[i].x);
        bounds.min.y = fmin(bounds.min.y, corners[i].y);
        bounds.min.z = fmin(bounds.min.z, corners[i].z);
        
        bounds.max.x = fmax(bounds.max.x, corners[i].x);
        bounds.max.y = fmax(bounds.max.y, corners[i].y);
        bounds.max.z = fmax(bounds.max.z, corners[i].z);
        i++;
    }
    return (ft_get_minimum_bounds(bounds));
}

t_bounds    ft_get_triangle_bounds(t_triangle tri)
{
    t_bounds bounds;

    bounds.min = tri.points.a;
    bounds.max = tri.points.a;
    int i = 1;
    while (i < 3)
    {
        bounds.min = ft_v3f_min(bounds.min, tri.points.p[i]);
        bounds.max = ft_v3f_max(bounds.max, tri.points.p[i]);
        i++;
    }
    return (ft_get_minimum_bounds(bounds));
}

