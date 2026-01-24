/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_builder_pl_objects.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:43:05 by pberne            #+#    #+#             */
/*   Updated: 2026/01/24 17:08:40 by pberne           ###   ########.fr       */
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
	t_list			*scene_lst;
	t_parsed_object	*copy;

	scene_lst = scene->object_lst;
	i = 0;
	while (lst)
	{
		element = lst->content;
		if (element->type == object_type_cylinder
			|| element->type == object_type_sphere)
		{
			copy = ft_malloc(sizeof(t_object));
			*copy = *element;
			ft_lstadd_front(&scene_lst, ft_lstnew_gc(copy));
			i++;
		}
		lst = lst->next;
	}
	scene->num_objects = i;
}

void ft_process_objects_bounds(t_scene *scene)
{
	t_list *lst;

	t_object *obj;

	lst = scene->object_lst;
	while (lst)
	{
		obj = lst->content;
		if (obj->type == object_type_sphere)
		{
			obj->bounds = ft_get_sphere_bounds(obj->object.as_sphere);
		}
	}
}
