/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_allocator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:22:05 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 22:56:39 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_allocate_textures(t_scene *scene, int *counts)
{
	scene->num_textures = counts[object_type_texture_path];
	if (scene->num_textures == 0)
		return ;
	scene->num_textures += 2;
	scene->textures = ft_malloc(sizeof(t_texture) * scene->num_textures);
	ft_bzero(scene->textures, sizeof(t_texture) * scene->num_textures);
}

void	ft_allocate_scene_data(t_scene *scene, int *counts)
{
	ft_allocate_textures(scene, counts);
	scene->planes = ft_malloc_id(sizeof(t_object) * counts[object_type_plane],
			malloc_id_scene);
	scene->lights = ft_malloc_id(sizeof(t_light) * counts[object_type_light],
			malloc_id_scene);
	scene->num_objects = counts[4] + counts[5] + counts[6] + counts[7]
		+ counts[8];
	scene->objects = ft_malloc_id(sizeof(t_object) * scene->num_objects,
			malloc_id_scene);
	scene->raw_objects = ft_malloc_id(sizeof(t_object) * scene->num_objects,
			malloc_id_scene);
	scene->bvh_node_capacity = scene->num_objects * 2;
	scene->bvh_nodes = ft_malloc_id(sizeof(t_bvh_node)
			* scene->bvh_node_capacity, malloc_id_scene);
	scene->bvh_node_count = 0;
}
