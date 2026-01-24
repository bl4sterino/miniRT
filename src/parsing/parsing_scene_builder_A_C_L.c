/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_builder_A_C_L.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:43:05 by pberne            #+#    #+#             */
/*   Updated: 2026/01/24 16:34:57 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_extract_camera(t_scene *scene, t_list *lst)
{
	t_parsed_object	*element;

	while (lst)
	{
		element = lst->content;
		if (element->type == object_type_camera)
		{
			scene->camera = element->object.as_camera;
			return ;
		}
		lst = lst->next;
	}
}

void	ft_extract_ambient_light(t_scene *scene, t_list *lst)
{
	t_parsed_object	*element;

	while (lst)
	{
		element = lst->content;
		if (element->type == object_type_ambient_light)
		{
			scene->ambient_light = element->object.as_ambient_light;
			return ;
		}
		lst = lst->next;
	}
}

void	ft_extract_lights(t_scene *scene, t_list *lst)
{
	int				i;
	t_parsed_object	*element;

	i = 0;
	while (lst)
	{
		element = lst->content;
		if (element->type == object_type_light)
		{
			scene->lights[i] = element->object.as_light;
			i++;
		}
		lst = lst->next;
	}
	scene->num_lights = i;
}
