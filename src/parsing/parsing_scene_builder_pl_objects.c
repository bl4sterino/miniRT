/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_builder_pl_objects.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:43:05 by pberne            #+#    #+#             */
/*   Updated: 2026/01/24 16:44:57 by pberne           ###   ########.fr       */
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
			scene->planes[i] = element->object.as_plane;
			i++;
		}
		lst = lst->next;
	}
	scene->num_planes = i;
}

void	ft_extract_objects(t_scene *scene, t_list *lst)
{
	int				i;
	t_parsed_object	*element;

	i = 0;
	while (lst)
	{
		element = lst->content;
		if (element->type == object_type_cylinder)
		{
			scene->objects[i].type = object_type_cylinder;
			scene->objects[i].object.as_cylinder = element->object.as_cylinder;
			i++;
		}
		if (element->type == object_type_sphere)
		{
			scene->objects[i].type = object_type_sphere;
			scene->objects[i].object.as_sphere = element->object.as_sphere;
			i++;
		}
		lst = lst->next;
	}
	scene->num_objects = i;
}
