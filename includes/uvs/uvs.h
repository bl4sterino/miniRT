/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:56:34 by pberne            #+#    #+#             */
/*   Updated: 2026/03/23 17:40:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UVS_H
# define UVS_H

# include "uv_cyl.h"
# include "uv_sp_pl_q_el.h"

static inline t_v2f	ft_get_hit_uv(t_v3f pos, int hit, t_scene *scene)
{
	t_object	object;

	if (hit < 0)
		return (ft_plane_uv(pos, scene->planes[-(hit + 1)].object.as_plane));
	object = scene->objects[hit];
	if (object.type == object_type_sphere)
		return (ft_sphere_uv(pos, object.object.as_sphere));
	else if (object.type == object_type_cylinder)
		return (ft_cylinder_uv(pos, object.object.as_cylinder));
	else if (object.type == object_type_quad)
		return (ft_quad_uv(pos, object.object.as_quad));
	else if (object.type == object_type_ellipsoid)
		return (ft_ellipsoid_uv(pos, object.object.as_ellipsoid));
	return ((t_v2f){0.0f, 0.0f});
}

static inline t_v2f	ft_normalize_uv(t_v2f uv)
{
	t_v2f	normalized;

	normalized.x = uv.x - floorf(uv.x);
	normalized.y = uv.y - floorf(uv.y);
	if (normalized.x < 0)
		normalized.x += 1.0f;
	if (normalized.y < 0)
		normalized.y += 1.0f;
	return (normalized);
}

static inline t_v3f	ft_checkerboard(t_v3f in_color, t_v2f uv)
{
	float	scale;
	int		u_check;
	int		v_check;
	t_v3f	inverted;

	scale = 20.0f;
	u_check = (int)floorf(uv.x * scale);
	v_check = (int)floorf(uv.y * scale);
	if ((u_check + v_check) % 2 == 0)
		return (in_color);
	else
	{
		inverted.x = 1.0f - in_color.x;
		inverted.y = 1.0f - in_color.y;
		inverted.z = 1.0f - in_color.z;
		return (inverted);
	}
}

#endif