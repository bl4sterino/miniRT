/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_builder_A_C_L_sky.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:43:05 by pberne            #+#    #+#             */
/*   Updated: 2026/04/07 17:13:59 by pberne           ###   ########.fr       */
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
			add_camera(scene, &element->object.as_camera);
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

void	ft_extract_skybox(t_scene *scene, t_list *lst)
{
	t_parsed_object	*element;
	int				color_id;
	int				lum_id;

	scene->skybox_tex.pixels = 0;
	scene->skybox_tex.ptr = 0;
	scene->skybox_tex.hdr_pixels = 0;
	scene->skybox_sphere = (t_sphere){(t_v3f){{0.0f, 0.0f, 0.0f, 0.0f}}, 1.0f};
	while (lst)
	{
		element = lst->content;
		if (element->type == object_type_skybox)
		{
			color_id = element->object.as_skybox.color;
			lum_id = element->object.as_skybox.luminance;
			if (color_id < 2 || lum_id < 2 || color_id > scene->num_textures
				|| lum_id > scene->num_textures)
				ft_exit_str_fd(1, "Skybox texture is out of range\n", 2);
			ft_create_hdr_tex(&scene->skybox_tex, &scene->textures[color_id],
				&scene->textures[lum_id]);
			return ;
		}
		lst = lst->next;
	}
}
