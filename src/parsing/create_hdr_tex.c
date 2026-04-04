/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hdr_tex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:42:24 by pberne            #+#    #+#             */
/*   Updated: 2026/04/04 20:48:54 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// Creates a copy of color_id tex and boosts it with a luminance texture
// Assigns a pointer to the source color texture to "pixels"
void	ft_create_hdr_tex(t_texture *out, t_texture *color, t_texture *lum)
{
	t_texture	tex;
	size_t		i;
	t_v3f		temp;
	size_t		size;

	tex.pixels = 0;
	tex.ptr = 0;
	size = color->width * color->height;
	if (color->width != lum->width || color->height != lum->height)
		ft_exit_str_fd(1, "Create HDR failed: textures have different sizes\n",
			2);
	tex.hdr_pixels = ft_malloc(color->width * color->height * sizeof(t_v3f));
	tex.width = color->width;
	tex.height = color->height;
	tex.pixels = color->pixels;
	i = 0;
	while (i < size)
	{
		temp = ft_int_to_v3f(color->pixels[i]);
		temp.v += temp.v * ft_int_to_v3f(lum->pixels[i]).v * MAX_HDR_COEF;
		tex.hdr_pixels[i] = temp;
		i++;
	}
	*out = tex;
}
