/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:44:44 by pberne            #+#    #+#             */
/*   Updated: 2026/03/23 19:15:10 by pberne           ###   ########.fr       */
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

static inline t_v3f	ft_checkerboard(t_v3f in_color, t_v2f uv);

#include <stdio.h>
static inline t_v3f ft_sample_texture(t_scene *scene, t_material mat , t_v2f uv)
{
	int x;
	int y;
	int index;
	
	x = scene->textures[mat.color_tex].width * uv.x;
	y = scene->textures[mat.color_tex].height * uv.y;
	index = (y * scene->textures[mat.color_tex].width) + x;

	t_texture tex = scene->textures[mat.color_tex];
	(void)tex;
	int int_color = tex.pixels[index];
	t_v3f color = ft_int_to_v3f(int_color);
	return color;
}
static inline t_v2f	ft_normalize_uv(t_v2f uv);

static inline t_v3f	ft_get_hit_color(t_scene *scene, t_material mat, t_v2f uv)
{
	if (mat.color_tex == 0)
		return (mat.color);
	uv = ft_normalize_uv(uv);
	if (mat.color_tex == -1 || mat.color_tex == 1)
		return (ft_checkerboard(mat.color, uv));
	else if(mat.color_tex > 0)
		return ft_sample_texture(scene, mat, uv);
	else
	{
		mat.color_tex = -mat.color_tex;
		return (ft_checkerboard(ft_sample_texture(scene, mat, uv), uv));
	}
		
}

#endif