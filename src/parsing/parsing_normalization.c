/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_normalization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:57:52 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 12:11:48 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_normalize_vectors(t_scene *scene)
{
	int	i;

	if (ft_v3d_length(scene->camera.direction) < 0.01)
		scene->camera.direction = (t_v3d){0, 1, 0};
	else
		scene->camera.direction = ft_v3d_normalize(scene->camera.direction);
	i = 0;
	while (i < scene->num_planes)
	{
		if (ft_v3d_length(scene->planes[i].normal) < 0.01)
			scene->planes[i].normal = (t_v3d){0, 1, 0};
		else
			scene->planes[i].normal = ft_v3d_normalize(scene->planes[i].normal);
		i++;
	}
	i = 0;
	while (i < scene->num_cylinders)
	{
		if (ft_v3d_length(scene->cylinders[i].normal) < 0.01)
			scene->cylinders[i].normal = (t_v3d){0, 1, 0};
		else
			scene->cylinders[i].normal
				= ft_v3d_normalize(scene->cylinders[i].normal);
		i++;
	}
}
