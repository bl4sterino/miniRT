/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_normalization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:57:52 by pberne            #+#    #+#             */
/*   Updated: 2026/02/26 15:22:12 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_normalize_camera(t_parsed_object *elem)
{
	if (ft_v3f_length(elem->object.as_camera.direction) < 0.01f)
		elem->object.as_camera.direction = (t_v3f){{0.0f, 0.0f, 1.0f}};
	else
		elem->object.as_camera.direction = ft_v3f_normalize(
				elem->object.as_camera.direction);
}

/* Normalizes a vector or defaults it to 0,0,1 if it is too small */
void	ft_normalize_vector(t_v3f *v)
{
	if (ft_v3f_length(*v) < 0.001f)
		*v = (t_v3f){{0.0f, 0.0f, 1.0f}};
	else
		*v = ft_v3f_normalize(*v);
}

void	ft_normalize_vectors(t_list *lst)
{
	t_parsed_object	*elem;

	while (lst)
	{
		elem = lst->content;
		if (elem->type == object_type_camera)
			ft_normalize_vector(&(elem->object.as_camera.direction));
		else if (elem->type == object_type_plane)
			ft_normalize_vector(&(elem->object.as_plane.normal));
		else if (elem->type == object_type_cylinder)
			ft_normalize_vector(&(elem->object.as_cylinder.normal));
		lst = lst->next;
	}
}
