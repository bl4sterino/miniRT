/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 19:44:09 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 14:00:24 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_color_lerp(int color1, int color2, float t)
{
	t_rgb	c1;
	t_rgb	c2;
	t_rgb	ret;

	c1 = (t_rgb){(color1 >> 16) & 0xFF, (color1 >> 8) & 0xFF, color1 & 0xFF};
	c2 = (t_rgb){(color2 >> 16) & 0xFF, (color2 >> 8) & 0xFF, color2 & 0xFF};
	ret = (t_rgb){ft_lerpi(c1.r, c2.r, t), ft_lerpi(c1.g, c2.g, t),
		ft_lerpi(c1.g, c2.g, t)};
	return (ret.r << 16 | ret.g << 8 | ret.b);
}

int	ft_color_lerp_rgb_to_int(t_rgb c1, t_rgb c2, float t)
{
	t_rgb	ret;

	ret = (t_rgb){ft_lerpi(c1.r, c2.r, t), ft_lerpi(c1.g, c2.g, t),
		ft_lerpi(c1.b, c2.b, t)};
	return (ret.r << 16 | ret.g << 8 | ret.b);
}

int	ft_rgb_to_int(t_rgb color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

int	ft_uc_color_to_int(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

t_rgb	ft_int_to_rgb(int color)
{
	return ((t_rgb){(color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF});
}
