/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_processing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:18:10 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 23:41:49 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_process_objects_bounds(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->num_objects)
	{
		if (scene->raw_objects[i].type == object_type_sphere)
			scene->raw_objects[i].bounds = ft_get_sphere_bounds(
					scene->raw_objects[i].object.as_sphere);
		else if (scene->raw_objects[i].type == object_type_cylinder)
			scene->raw_objects[i].bounds = ft_get_cylinder_bounds(
					scene->raw_objects[i].object.as_cylinder);
		else if (scene->raw_objects[i].type == object_type_quad)
			scene->raw_objects[i].bounds = ft_get_quad_bounds(
					scene->raw_objects[i].object.as_quad);
		else if (scene->raw_objects[i].type == object_type_triangle)
			scene->raw_objects[i].bounds = ft_get_triangle_bounds(
					scene->raw_objects[i].object.as_triangle);
		else if (scene->raw_objects[i].type == object_type_ellipsoid)
			scene->raw_objects[i].bounds = ft_get_ellipsoid_bounds(
					scene->raw_objects[i].object.as_ellipsoid);
		i++;
	}
}

void	ft_count_matches(t_list *lst, int *counts)
{
	t_parsed_object	*element;

	while (lst)
	{
		element = lst->content;
		counts[element->type]++;
		lst = lst->next;
	}
}

void	ft_preprocess_pdfs(t_scene *scene)
{
	int		i;
	float	area;
	float	pdf;

	i = 0;
	while (i < scene->emissive_objects)
	{
		area = ft_get_object_area(scene->raw_objects[i]);
		pdf = 1.0f / (area * (float)scene->emissive_objects);
		scene->raw_objects[i].pdf = pdf * PI;
		i++;
	}
}

void	ft_setup_emissive_objects(t_scene *scene)
{
	int	emissive_count;
	int	i;

	emissive_count = 0;
	i = 0;
	while (i < scene->num_objects)
	{
		if (scene->raw_objects[i].material.emission > 0.0f)
		{
			scene->raw_objects[i].material.color = ft_v3f_scale(
					scene->raw_objects[i].material.color,
					scene->raw_objects[i].material.emission);
			ft_swap_objects(&scene->raw_objects[i],
				&scene->raw_objects[emissive_count]);
			scene->raw_objects[i].raw_id = i;
			scene->raw_objects[emissive_count].raw_id = emissive_count;
			emissive_count++;
		}
		i++;
	}
	scene->emissive_objects = emissive_count;
	ft_preprocess_pdfs(scene);
}
