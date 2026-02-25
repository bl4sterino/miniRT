/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_builder_A_C_L.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:43:05 by pberne            #+#    #+#             */
/*   Updated: 2026/02/25 14:19:02 by pberne           ###   ########.fr       */
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
	t_v3f			color;

	while (lst)
	{
		element = lst->content;
		if (element->type == object_type_ambient_light)
		{
			scene->ambient_light = element->object.as_ambient_light;
			color = ft_v3f_scale(scene->ambient_light.color,
					scene->ambient_light.intensity);
			scene->ambient_light.rgb_int_color = ft_v3f_to_int_color(color);
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
			scene->lights[i].color = ft_v3f_scale(scene->lights[i].color,
					scene->lights[i].intensity);
			i++;
		}
		lst = lst->next;
	}
	scene->num_lights = i;
}
