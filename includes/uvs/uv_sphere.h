/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_sphere.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:52:27 by pberne            #+#    #+#             */
/*   Updated: 2026/03/20 16:18:43 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UV_SPHERE_H
# define UV_SPHERE_H

# include "rt.h"
# include <math.h>

static inline t_v2f	ft_sphere_uv(t_v3f point, t_sphere sp)
{
	t_v2f	uv;
	t_v3f	d;
	float	phi;
	float	theta;

	d.x = (point.x - sp.position.x) / sp.radius;
	d.y = (point.y - sp.position.y) / sp.radius;
	d.z = (point.z - sp.position.z) / sp.radius;
	phi = atan2f(d.z, d.x);
	theta = asinf(d.y);
	uv.x = 1 - (phi + PI) / (2.0f * PI);
	uv.y = (theta + PI / 2.0f) / PI;
	return (uv);
}

#endif