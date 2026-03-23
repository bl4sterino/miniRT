/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_conversions_inlined.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:28:26 by pberne            #+#    #+#             */
/*   Updated: 2026/03/23 19:03:05 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_CONVERSIONS_INLINED_H
# define COLORS_CONVERSIONS_INLINED_H

# include "rt.h"

static inline int	ft_rgb_to_int(t_rgb color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

static inline t_rgb	ft_int_to_rgb(int color)
{
	return ((t_rgb){(color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF});
}

static inline t_v3f	ft_int_to_v3f(int color)
{
	return ((t_v3f){{(float)((color >> 16) & 0xFF) * 0.003921569f,
		(float)((color >> 8) & 0xFF) * 0.003921569f, (float)(color & 0xFF)
		* 0.003921569f}});
}

static inline int	ft_v3d_to_int_color(t_v3d color)
{
	return ((int)(color.x * 255) << 16 | (int)(color.y
			* 255) << 8 | (int)(color.z * 255));
}

static inline int	ft_v3f_to_int_color(t_v3f color)
{
	return ((int)(color.x * 255) << 16 | (int)(color.y
			* 255) << 8 | (int)(color.z * 255));
}

static inline int	ft_doubles_to_int_color(double r, double g, double b)
{
	return ((int)(r * 255) << 16 | (int)(g * 255) << 8 | (int)(b * 255));
}

#endif
