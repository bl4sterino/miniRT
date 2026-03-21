/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_sp_pl_q_el.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:52:27 by pberne            #+#    #+#             */
/*   Updated: 2026/03/21 16:44:37 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UV_SP_PL_Q_EL_H
# define UV_SP_PL_Q_EL_H

# include "rt.h"
# include <math.h>

static inline t_v2f	ft_sphere_uv(t_v3f point, t_sphere sp)
{
	t_v2f	uv;
	t_v3f	d;
	float	phi;
	float	theta;

	d.v = (point.v - sp.position.v) / sp.radius;
	phi = atan2f(d.z, d.x);
	theta = asinf(d.y);
	uv.x = 1 - (phi + PI) / (2.0f * PI);
	uv.y = (theta + PI / 2.0f) / PI;
	return (uv);
}

static inline t_v2f	ft_quad_uv(t_v3f hit_p, t_quad quad)
{
	t_v2f	uv;
	t_v3f	d;

	d = ft_v3f_sub(hit_p, quad.position);
	uv.x = (ft_v3f_dot(d, quad.u_axis) / quad.size.x) + 0.5f;
	uv.y = (ft_v3f_dot(d, quad.v_axis) / quad.size.y) + 0.5f;
	return (uv);
}

static inline t_v2f	ft_plane_uv(t_v3f hit_p, t_plane plane)
{
	t_v2f	uv;
	t_v3f	u_axis;
	t_v3f	v_axis;
	t_v3f	d;

	d = ft_v3f_sub(hit_p, plane.position);
	if (fabsf(plane.normal.y) < 0.999f)
		u_axis = ft_v3f_normalize(ft_v3f_cross(plane.normal, (t_v3f){{0, 1,
					0}}));
	else
		u_axis = ft_v3f_normalize(ft_v3f_cross(plane.normal, (t_v3f){{0, 0,
					1}}));
	v_axis = ft_v3f_cross(plane.normal, u_axis);
	uv.x = ft_v3f_dot(d, u_axis) * 0.005f;
	uv.y = ft_v3f_dot(d, v_axis) * 0.005f;
	return (uv);
}

static inline t_v2f	ft_ellipsoid_uv(t_v3f hit_p, t_ellipsoid el)
{
	t_v2f	uv;
	t_v3f	d;
	float	phi;
	float	theta;

	d.x = (hit_p.x - el.position.x) / el.radii.x;
	d.y = (hit_p.y - el.position.y) / el.radii.y;
	d.z = (hit_p.z - el.position.z) / el.radii.z;
	d = ft_v3f_normalize(d);
	phi = atan2f(d.z, d.x);
	theta = asinf(d.y);
	uv.x = 1.0f - (phi + M_PI) / (2.0f * M_PI);
	uv.y = (theta + M_PI_2) / M_PI;
	return (uv);
}

#endif