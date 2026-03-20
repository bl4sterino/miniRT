/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:56:34 by pberne            #+#    #+#             */
/*   Updated: 2026/03/20 16:18:33 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UVS_H
# define UVS_H

# include "uv_sphere.h"

static inline t_v2f	ft_get_hit_uv(t_v3f pos, int hit, t_scene *scene)
{
	t_object	object;

	if (hit < 0)
		return ((t_v2f){0.0f, 0.0f});
	object = scene->objects[hit];
	if (object.type == object_type_sphere)
		return (ft_sphere_uv(pos, object.object.as_sphere));
	return ((t_v2f){0.0f, 0.0f});
}

static inline t_v3f	ft_checkerboard(t_v3f in_color, t_v2f uv)
{
	float	scale;
	int		u_check;
	int		v_check;
		t_v3f inverted;

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