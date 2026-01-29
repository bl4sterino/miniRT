/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_builder_pl_objects.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:43:05 by pberne            #+#    #+#             */
/*   Updated: 2026/01/28 10:17:53 by pberne           ###   ########.fr       */
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

t_object	*ft_copy_parsed_object_to_object(t_parsed_object *parsed_object)
{
	t_object	*copy;

	copy = ft_malloc(sizeof(t_object));
	copy->type = parsed_object->type;
	if (copy->type == object_type_sphere)
		copy->object.as_sphere = parsed_object->object.as_sphere;
	if (copy->type == object_type_cylinder)
		copy->object.as_cylinder = parsed_object->object.as_cylinder;
	return (copy);
}

void	ft_extract_objects(t_scene *scene, t_list *lst)
{
	int				size;
	t_parsed_object	*po;
	int				i;

	size = ft_lstsize(lst);
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
