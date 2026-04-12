/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_push_planes_tex_sky.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:22:05 by pberne            #+#    #+#             */
/*   Updated: 2026/04/13 00:21:08 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_push_plane(t_scene *scene, t_extraction_counts *counts,
		t_parsed_object *po)
{
	ft_normalize_vector(&(po->object.as_plane.normal));
	if (ft_abs(po->material.color_tex) > scene->num_textures
		|| ft_abs(po->material.normal_tex) > scene->num_textures)
		ft_exit_str_fd(1, "Ivalid texture index\n", 2);
	scene->planes[counts->planes].object.as_plane = po->object.as_plane;
	scene->planes[counts->planes].material = po->material;
	counts->planes++;
}

void	ft_push_tex(t_data *d, t_scene *scene, t_extraction_counts *c,
		t_parsed_object *po)
{
	ft_try_extract_texture(d, &scene->textures[--c->textures],
		po->object.as_texture_path);
}

void	ft_prepare_sky(t_scene *scene, t_extraction_counts *c,
		t_parsed_object *po)
{
	c->sky_color = po->object.as_skybox.color;
	c->sky_lum = po->object.as_skybox.luminance;
	if (c->sky_color < 2 || c->sky_lum < 2 || c->sky_color > scene->num_textures
		|| c->sky_lum > scene->num_textures)
		ft_exit_str_fd(1, "Skybox texture is out of range\n", 2);
}

void	ft_push_sky(t_scene *scene, t_extraction_counts *c)
{
	int	color_id;
	int	lum_id;

	color_id = c->sky_color;
	lum_id = c->sky_lum;
	if (color_id == 0 && lum_id == 0)
		return ;
	if (color_id < 2 || lum_id < 2 || color_id > scene->num_textures
		|| lum_id > scene->num_textures)
		ft_exit_str_fd(1, "Skybox texture is out of range\n", 2);
	ft_create_hdr_tex(&scene->skybox_tex, &scene->textures[color_id],
		&scene->textures[lum_id]);
}
