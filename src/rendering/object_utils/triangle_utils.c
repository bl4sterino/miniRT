/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 08:37:40 by pberne            #+#    #+#             */
/*   Updated: 2026/04/11 12:51:55 by pberne           ###   ########.fr       */
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
	if (fabsf(c.denom) < EPSILON)
	{
		tri_uv->x = 0.0f;
		tri_uv->y = 0.0f;
		return ;
	}
	tri_uv->x = (c.d11 * c.d20 - c.d01 * c.d21) / c.denom;
	tri_uv->y = (c.d00 * c.d21 - c.d01 * c.d20) / c.denom;
}

t_v3f	ft_triangle_normal(t_triangle tri, t_v2f tri_uv, t_v3f ray)
{
	t_v3f	interp_n;
	float	w;

	(void) ray;
	w = 1.0f - tri_uv.x - tri_uv.y;
	interp_n.x = (w * tri.normals[0].x) + (tri_uv.x * tri.normals[1].x)
		+ (tri_uv.y * tri.normals[2].x);
	interp_n.y = (w * tri.normals[0].y) + (tri_uv.x * tri.normals[1].y)
		+ (tri_uv.y * tri.normals[2].y);
	interp_n.z = (w * tri.normals[0].z) + (tri_uv.x * tri.normals[1].z)
		+ (tri_uv.y * tri.normals[2].z);
	if (ft_v3f_dot(tri.normal, ray) < 0)
		interp_n.v *= -1;
	return (interp_n);
}

t_v2f	ft_triangle_uv(t_v3f pos, t_triangle tri, t_v2f tri_uv)
{
	t_v2f	final_uv;
	float	w;

	if (tri_uv.x == -1.0f)
		ft_set_triangle_object_uv(pos, tri, &tri_uv);
	w = fmaxf(1.0f - tri_uv.x - tri_uv.y, 0.0f);
	final_uv.x = (w * tri.uvs[0].x) + (tri_uv.x * tri.uvs[1].x) + (tri_uv.y
			* tri.uvs[2].x);
	final_uv.y = (w * tri.uvs[0].y) + (tri_uv.x * tri.uvs[1].y) + (tri_uv.y
			* tri.uvs[2].y);
	return (final_uv);
}
