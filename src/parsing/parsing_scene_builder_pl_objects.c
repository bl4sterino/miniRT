/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_builder_pl_objects.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:43:05 by pberne            #+#    #+#             */
/*   Updated: 2026/01/29 18:07:00 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_extract_planes(t_scene *scene, t_list *lst)
{
	int				i;
	t_parsed_object	*element;

	i = 0;
	while (lst)
	{
		element = lst->content;
		if (element->type == object_type_plane)
		{
			scene->planes[i].object.as_plane = element->object.as_plane;
			scene->planes[i].material = element->material;
			i++;
		}
		lst = lst->next;
	}
	scene->num_planes = i;
}


void	ft_extract_objects(t_scene *scene, t_list *lst)
{
	int				size;
	t_parsed_object	*po;
	int				i;

	size = ft_count_matches(lst, object_type_sphere) + ft_count_matches(lst, object_type_cylinder);
	if (size == 0)
		return ;
	scene->objects = ft_malloc(sizeof(t_object) * size);
	i = 0;
	while (lst)
	{
		po = lst->content;
		if (po->type == object_type_sphere || po->type == object_type_cylinder)
		{
			scene->objects[i].type = po->type;
			scene->objects[i].material = po->material;
			if (po->type == object_type_sphere)
				scene->objects[i].object.as_sphere = po->object.as_sphere;
			else if (po->type == object_type_cylinder)
				scene->objects[i].object.as_cylinder = po->object.as_cylinder;
			i++;
		}
		lst = lst->next;
	}
	scene->num_objects = i;
}

void	ft_process_objects_bounds(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->num_objects)
	{
		if (scene->objects[i].type == object_type_sphere)
		{
			scene->objects[i].bounds = ft_get_sphere_bounds(
					scene->objects[i].object.as_sphere);
		}
		else if (scene->objects[i].type == object_type_cylinder)
		{
			scene->objects[i].bounds = ft_get_cylinder_bounds(
					scene->objects[i].object.as_cylinder);
		}
		i++;
	}
}
