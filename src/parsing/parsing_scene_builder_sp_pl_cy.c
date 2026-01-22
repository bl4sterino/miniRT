/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_builder_sp_pl_cy.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 07:43:05 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 09:09:02 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_extract_spheres(t_scene *scene, t_list *lst)
{
	int					i;
	t_object_element	*element;

	i = 0;
	while (lst)
	{
		element = lst->content;
		if (element->type == object_type_sphere)
		{
			scene->spheres[i] = element->object.as_sphere;
			i++;
		}
		lst = lst->next;
	}
}

void	ft_extract_planes(t_scene *scene, t_list *lst)
{
	int					i;
	t_object_element	*element;

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
}

void	ft_extract_cylinder(t_scene *scene, t_list *lst)
{
	int					i;
	t_object_element	*element;

	i = 0;
	while (lst)
	{
		element = lst->content;
		if (element->type == object_type_cylinder)
		{
			scene->cylinders[i] = element->object.as_cylinder;
			i++;
		}
		lst = lst->next;
	}
}
