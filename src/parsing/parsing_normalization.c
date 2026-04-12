/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_normalization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:57:52 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 22:54:38 by pberne           ###   ########.fr       */
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
