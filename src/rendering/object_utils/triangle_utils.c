/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 08:37:40 by pberne            #+#    #+#             */
/*   Updated: 2026/04/10 09:20:31 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_set_triangle_object_uv(t_v3f hit_p, t_triangle tri, t_v2f *tri_uv)
{
	t_set_triangle_object_uv_context	c;

	c.v0v1 = ft_v3f_sub(tri.points[1], tri.points[0]);
	c.v0v2 = ft_v3f_sub(tri.points[2], tri.points[0]);
	c.v0p = ft_v3f_sub(hit_p, tri.points[0]);
	c.d00 = ft_v3f_dot(c.v0v1, c.v0v1);
	c.d01 = ft_v3f_dot(c.v0v1, c.v0v2);
	c.d11 = ft_v3f_dot(c.v0v2, c.v0v2);
	c.d20 = ft_v3f_dot(c.v0p, c.v0v1);
	c.d21 = ft_v3f_dot(c.v0p, c.v0v2);
	c.denom = c.d00 * c.d11 - c.d01 * c.d01;
	if (fabsf(c.denom) < 1e-6f)
	{
		tri_uv->x = 0.0f;
		tri_uv->y = 0.0f;
		return ;
	}
	tri_uv->x = (c.d11 * c.d20 - c.d01 * c.d21) / c.denom;
	tri_uv->y = (c.d00 * c.d21 - c.d01 * c.d20) / c.denom;
}

t_v3f	ft_triangle_normal(t_v3f pos, t_triangle tri)
{
	t_v3f	normal;
	t_v2f	tri_uv;

	ft_set_triangle_object_uv(pos, tri, &tri_uv);
	normal.v = tri.normals[0].v * (1.0f - tri_uv.x) + tri.normals[1].v
		* tri_uv.x;
	normal.v = normal.v * (1.0f - tri_uv.y) + tri.normals[2].v * tri_uv.y;
	return (normal);
}

t_v2f	ft_triangle_uv(t_v3f pos, t_triangle tri)
{
	t_v3f	uv;
	t_v2f	tri_uv;

	ft_set_triangle_object_uv(pos, tri, &tri_uv);
	uv.v = tri.uvs[0].v * (1.0f - tri_uv.x) + tri.uvs[1].v * tri_uv.x;
	uv.v = uv.v * (1.0f - tri_uv.y) + tri.uvs[2].v * tri_uv.y;
	return ((t_v2f){uv.x, uv.y});
}
