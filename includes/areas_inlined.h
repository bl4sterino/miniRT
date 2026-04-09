/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   areas_inlined.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 22:54:45 by pberne            #+#    #+#             */
/*   Updated: 2026/04/09 19:17:12 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AREAS_INLINED_H
# define AREAS_INLINED_H

# include "rt.h"

static inline float	ft_sphere_area(t_sphere sphere)
{
	return (4.0f * PI * sphere.radius * sphere.radius);
}

static inline float	ft_cylinder_area(t_cylinder cylinder)
{
	float	radius;

	radius = cylinder.diameter * 0.5f;
	return (2.0f * PI * radius * cylinder.height + 2.0 * PI * radius * radius);
}

static inline float	ft_quad_area(t_quad quad)
{
	return (quad.size.x * quad.size.y);
}

static inline float	ft_triangle_area(t_triangle tri)
{
	t_v3f	ab;
	t_v3f	ac;
	t_v3f	cross;
	float	mag_sq;

	ab = ft_v3f_sub(tri.points[1], tri.points[0]);
	ac = ft_v3f_sub(tri.points[2], tri.points[0]);
	cross.x = ab.y * ac.z - ab.z * ac.y;
	cross.y = ab.z * ac.x - ab.x * ac.z;
	cross.z = ab.x * ac.y - ab.y * ac.x;
	mag_sq = (cross.x * cross.x) + (cross.y * cross.y) + (cross.z * cross.z);
	return (0.5f * sqrtf(mag_sq));
}

static inline float	ft_get_object_area(t_object object)
{
	if (object.type == object_type_sphere)
		return (ft_sphere_area(object.object.as_sphere));
	else if (object.type == object_type_cylinder)
		return (ft_cylinder_area(object.object.as_cylinder));
	else if (object.type == object_type_quad)
		return (ft_quad_area(object.object.as_quad));
	else if (object.type == object_type_triangle)
		return (ft_triangle_area(object.object.as_triangle));
	return (1.0f);
}

#endif
