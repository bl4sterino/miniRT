/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_side_inlined.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:31:48 by pberne            #+#    #+#             */
/*   Updated: 2026/03/09 14:19:42 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_SIDE_INLINED_H
# define HIT_SIDE_INLINED_H

# include "rt.h"

static inline char	ft_side_sphere(t_v3f hitpoint, t_sphere sphere)
{
	float	dist;

	dist = ft_v3f_length_squared(ft_v3f_sub(hitpoint, sphere.position));
	if (dist > sphere.radius * sphere.radius)
		return (1);
	return (-1);
}

static inline char	ft_side_ellipsoid(t_v3f hitpoint, t_ellipsoid el)
{
	t_v3f	oc;
	float	equation_result;

	oc = ft_v3f_sub(hitpoint, el.position);
	equation_result = (oc.x * oc.x * el.inv_r2.x) + (oc.y * oc.y * el.inv_r2.y)
		+ (oc.z * oc.z * el.inv_r2.z);
	if (equation_result > 1.0f + EPSILON)
		return (1);
	return (-1);
}

static inline char	ft_get_hit_side(t_scene *scene, t_v3f hitpoint,
		int object_id)
{
	t_object	obj;

	if (object_id < 0)
		obj = scene->planes[-object_id - 1];
	else
		obj = scene->objects[object_id];
	if (obj.type == object_type_sphere)
		return (ft_side_sphere(hitpoint, obj.object.as_sphere));
	else if (obj.type == object_type_ellopsoid)
		return (ft_side_ellipsoid(hitpoint, obj.object.as_ellipsoid));
	return (0);
}

#endif