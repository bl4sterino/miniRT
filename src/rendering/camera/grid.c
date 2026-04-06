/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:34:00 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/06 19:57:42 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	recompute_grid(t_scene *scene, t_rect rect)
{
	int	s;
	int	i;
	int	grid_h;
	int	last;

	s = 1;
	while (s * s < scene->num_cameras)
		s++;
	grid_h = 1;
	while (grid_h * s < scene->num_cameras)
		grid_h++;
	last = scene->num_cameras - (grid_h - 1) * s;
	i = 0;
	while (i < scene->num_cameras)
	{
		if (i / s == grid_h - 1)
			scene->cameras[i].rect = (t_rect){.x = (i % s) * (rect.w / last),
				.y = (i / s) * (rect.h / grid_h), .w = rect.w / last,
				.h = rect.h / grid_h};
		else
			scene->cameras[i].rect = (t_rect){.x = (i % s) * (rect.w / s),
				.y = (i / s) * (rect.h / grid_h), .w = rect.w / s,
				.h = rect.h / grid_h};
		i++;
	}
}
