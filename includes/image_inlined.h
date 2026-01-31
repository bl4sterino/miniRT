/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_inlined.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:52:50 by pberne            #+#    #+#             */
/*   Updated: 2026/01/31 12:56:22 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_INLINED_H
# define IMAGE_INLINED_H

# include "rt.h"

static inline void	ft_put_pxl(char *imageaddr, t_v2i pos, int color)
{
	char	*pixel;

	if (pos.x >= 0 && pos.x < WIDTH_WIN && pos.y >= 0 && pos.y < HEIGHT_WIN)
	{
		pixel = imageaddr + (pos.y * LINE_SIZE + pos.x * IMAGE_BPP);
		*(int *)pixel = color;
	}
}

static inline int	ft_rgb_to_int(t_rgb color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

static inline t_rgb	ft_int_to_rgb(int color)
{
	return ((t_rgb){(color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF});
}

static inline int	ft_v3d_to_int_color(t_v3d color)
{
	return ((int)(color.x * 255) << 16 | (int)(color.y
			* 255) << 8 | (int)(color.z * 255));
}

static inline int	ft_color_lerp(int color1, int color2, float t)
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

void				ft_put_pxl_d(t_image *img, t_v2i pos, int color,
						float depth);
void				ft_create_image(t_data *d);
void				ft_draw_rectangle(t_image image, t_v2i pos, t_v2i size,
						t_rgb color);
int					ft_uc_color_to_int(unsigned char r, unsigned char g,
						unsigned char b);
int					ft_color_lerp_rgb_to_int(t_rgb c1, t_rgb c2, float t);

#endif