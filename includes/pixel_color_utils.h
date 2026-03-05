/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:44:44 by pberne            #+#    #+#             */
/*   Updated: 2026/03/05 13:47:31 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXEL_COLOR_UTILS_H
# define PIXEL_COLOR_UTILS_H

# include "rt.h"

static inline t_v3f	ft_get_sky_color(t_ray ray)
{
	float	dot;

	dot = (float)ft_v3f_dot(ray.direction, (t_v3f){{0.0f, 1.0f, 0.0f}});
	dot = (dot + 1) * 0.5f;
	dot = 0.05f + 0.1f * dot;
	return ((t_v3f){{dot, dot, dot}});
}

#endif