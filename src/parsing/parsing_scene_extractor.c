/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_extractor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:22:05 by pberne            #+#    #+#             */
/*   Updated: 2026/04/13 00:20:50 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_push_object(t_data *d, t_scene *scene, t_extraction_counts *counts,
		t_parsed_object *po)
{
	if (po->type >= object_type_sphere && po->type < object_type_texture_path)
		ft_push_shapes(scene, counts, po);
	else if (po->type == object_type_ambient_light)
		ft_push_a(scene, po);
	else if (po->type == object_type_camera)
		ft_push_c(scene, po);
	else if (po->type == object_type_light)
		ft_push_l(scene, counts, po);
	else if (po->type == object_type_skybox)
		ft_prepare_sky(scene, counts, po);
	else if (po->type == object_type_plane)
		ft_push_plane(scene, counts, po);
	else if (po->type == object_type_texture_path)
		ft_push_tex(d, scene, counts, po);
}

void	ft_extract_scene_data(t_data *d, t_scene *scene, t_list *lst,
	int texture_count)
{
	t_extraction_counts	counts;
	t_parsed_object		*po;

	ft_bzero(&counts, sizeof(t_extraction_counts));
	scene->skybox_tex.pixels = 0;
	scene->skybox_tex.ptr = 0;
	scene->skybox_tex.hdr_pixels = 0;
	counts.textures = texture_count + 2;
	counts.sky_color = 0;
	counts.sky_lum = 0;
	scene->skybox_sphere = (t_sphere){(t_v3f){{0.0f, 0.0f, 0.0f, 0.0f}}, 1.0f};
	while (lst)
	{
		po = lst->content;
		ft_push_object(d, scene, &counts, po);
		lst = lst->next;
	}
	ft_push_sky(scene, &counts);
}
