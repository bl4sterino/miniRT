/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:44:44 by pberne            #+#    #+#             */
/*   Updated: 2026/04/09 17:51:56 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXEL_COLOR_UTILS_H
# define PIXEL_COLOR_UTILS_H

# include "rt.h"

static inline t_v3f	ft_checkerboard(t_v3f in_color, t_v2f uv);

typedef struct s_sample_texture_context
{
	t_v3f			colors[4];
	float			dx;
	float			dy;
	t_v3f			top;
	t_v3f			bot;
	float			fx;
	float			fy;
	int				x;
	int				y;
	int				x1;
	int				y1;
}					t_sample_texture_context;

static inline t_v3f	ft_sample_texture_hdr(t_texture *tex, t_v2f uv)
{
	t_sample_texture_context	c;

	c.fx = uv.x * (tex->width - 1);
	c.fy = uv.y * (tex->height - 1);
	c.x = (int)c.fx;
	c.y = (int)c.fy;
	c.dx = c.fx - (float)c.x;
	c.dy = c.fy - (float)c.y;
	c.x1 = fmaxf(0, fminf(c.x + 1, tex->width - 1));
	c.y1 = fmaxf(0, fminf(c.y + 1, tex->height - 1));
	c.colors[0] = tex->hdr_pixels[c.y * tex->width + c.x];
	c.colors[1] = tex->hdr_pixels[c.y * tex->width + c.x1];
	c.colors[2] = tex->hdr_pixels[c.y1 * tex->width + c.x];
	c.colors[3] = tex->hdr_pixels[c.y1 * tex->width + c.x1];
	c.top.v = c.colors[0].v * (1.0f - c.dx) + c.colors[1].v * c.dx;
	c.bot.v = c.colors[2].v * (1.0f - c.dx) + c.colors[3].v * c.dx;
	return ((t_v3f){.v = c.top.v * (1.0f - c.dy) + c.bot.v * c.dy});
}

// Performs bilinear filtering
static inline t_v3f	ft_sample_texture(t_texture *tex, t_v2f uv)
{
	t_sample_texture_context	c;

	c.fx = uv.x * (tex->width - 1);
	c.fy = uv.y * (tex->height - 1);
	c.x = (int)c.fx;
	c.y = (int)c.fy;
	c.dx = c.fx - (float)c.x;
	c.dy = c.fy - (float)c.y;
	c.x1 = fmaxf(0, fminf(c.x + 1, tex->width - 1));
	c.y1 = fmaxf(0, fminf(c.y + 1, tex->height - 1));
	c.colors[0] = ft_int_to_v3f(tex->pixels[c.y * tex->width + c.x]);
	c.colors[1] = ft_int_to_v3f(tex->pixels[c.y * tex->width + c.x1]);
	c.colors[2] = ft_int_to_v3f(tex->pixels[c.y1 * tex->width + c.x]);
	c.colors[3] = ft_int_to_v3f(tex->pixels[c.y1 * tex->width + c.x1]);
	c.top.v = c.colors[0].v * (1.0f - c.dx) + c.colors[1].v * c.dx;
	c.bot.v = c.colors[2].v * (1.0f - c.dx) + c.colors[3].v * c.dx;
	return ((t_v3f){.v = c.top.v * (1.0f - c.dy) + c.bot.v * c.dy});
}

static inline t_v3f	ft_get_hit_color(t_scene *scene, t_material mat, t_v2f uv)
{
	if (mat.color_tex == 0)
		return (mat.color);
	if (mat.color_tex == -1 || mat.color_tex == 1)
		return (ft_checkerboard(mat.color, uv));
	else if (mat.color_tex > 0)
		return ((t_v3f){.v = ft_sample_texture(&scene->textures[mat.color_tex],
				uv).v * mat.color.v});
	else
	{
		mat.color_tex = -mat.color_tex;
		return (ft_checkerboard((t_v3f){
				.v = ft_sample_texture(&scene->textures[mat.color_tex],
					uv).v * mat.color.v}, uv));
	}
}

typedef struct s_texture_normal_context
{
	t_v3f			tex_color;
	t_v3f			map_n;
	t_v3f			helper;
	t_v3f			tangent;
	t_v3f			bitangent;
	t_v3f			final_n;
}					t_texture_normal_context;

static inline t_v3f	ft_apply_texture_normal(t_scene *scene, t_v3f normal,
		int tex_id, t_v2f uv)
{
	t_texture_normal_context	c;

	if (fabs(normal.v[1]) < 0.999f)
		c.helper = (t_v3f){{0.0f, 1.0f, 0.0f}};
	else
		c.helper = (t_v3f){{1.0f, 0.0f, 0.0f}};
	if (tex_id > 0)
		c.tex_color = ft_sample_texture(&scene->textures[tex_id], uv);
	else
	{
		tex_id = -tex_id;
		c.tex_color = ft_checkerboard(
				ft_sample_texture(&scene->textures[tex_id], uv), uv);
	}
	c.map_n.v[0] = (c.tex_color.v[0] * 2.0f - 1.0f);
	c.map_n.v[1] = ((1.0f - c.tex_color.v[1]) * 2.0f - 1.0f);
	c.map_n.v[2] = c.tex_color.v[2] * 2.0f - 1.0f;
	c.tangent = ft_v3f_normalize(ft_v3f_cross(c.helper, normal));
	c.bitangent = ft_v3f_cross(normal, c.tangent);
	c.final_n.v = (c.tangent.v * c.map_n.v[0]) + (c.bitangent.v * c.map_n.v[1])
		+ (normal.v * c.map_n.v[2]);
	return (ft_v3f_normalize(c.final_n));
}

#endif
