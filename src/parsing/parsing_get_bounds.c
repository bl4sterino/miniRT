/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_bounds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:09:03 by pberne            #+#    #+#             */
/*   Updated: 2026/01/29 17:05:41 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_bounds	ft_get_sphere_bounds(t_sphere sphere)
{
	t_v3d		v_radius;
	t_bounds	bounds;

	v_radius = (t_v3d){{sphere.radius, sphere.radius, sphere.radius}};
	bounds.min = ft_v3d_sub(sphere.position, v_radius);
	bounds.max = ft_v3d_add(sphere.position, v_radius);
	return (bounds);
}

t_bounds	ft_get_cylinder_bounds(t_cylinder cyl)
{
	t_bounds	bounds;
	t_v3d		p1;
	t_v3d		p2;
	t_v3d		extent;
	t_v2d		r_hh;

	r_hh.y = cyl.height / 2.0;
	r_hh.x = cyl.diameter / 2.0;
	p1 = ft_v3d_add(cyl.position, ft_v3d_scale(cyl.normal, r_hh.y));
	p2 = ft_v3d_sub(cyl.position, ft_v3d_scale(cyl.normal, r_hh.y));
	extent.x = r_hh.x * sqrt(1.0 - (cyl.normal.x * cyl.normal.x));
	extent.y = r_hh.x * sqrt(1.0 - (cyl.normal.y * cyl.normal.y));
	extent.z = r_hh.x * sqrt(1.0 - (cyl.normal.z * cyl.normal.z));
	bounds.min.x = fmin(p1.x, p2.x) - extent.x;
	bounds.min.y = fmin(p1.y, p2.y) - extent.y;
	bounds.min.z = fmin(p1.z, p2.z) - extent.z;
	bounds.max.x = fmax(p1.x, p2.x) + extent.x;
	bounds.max.y = fmax(p1.y, p2.y) + extent.y;
	bounds.max.z = fmax(p1.z, p2.z) + extent.z;
	return (bounds);
}
