/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:43:00 by pberne            #+#    #+#             */
/*   Updated: 2026/04/07 18:05:43 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_set_all_cameras_dirty(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->scene->num_cameras)
	{
		d->scene->cameras[i].dirty = 1;
		d->scene->cameras[i].cache_frame = 1;
		d->scene->cameras[i].frame_count = 0.0f;
		i++;
	}
}

void ft_clear_dirty_cameras(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->scene->num_cameras)
	{
		if (d->scene->cameras[i].dirty)
		{
			
		}
	}
	ft_memset_int(d->image.current_frame, 0, SCREEN_SIZE * 4);
	ft_memset_int(d->image.ray_targets, SELECTED_NONE, SCREEN_SIZE);
}