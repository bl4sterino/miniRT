/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:43:00 by pberne            #+#    #+#             */
/*   Updated: 2026/04/08 12:57:52 by pberne           ###   ########.fr       */
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
	d->dirty_frame = 0;
}

void	ft_memset_rect(void *p, int image_width, t_rect r, int value)
{
	int	y;

	y = 0;
	while (y < r.h)
	{
		ft_memset_int(p + ((r.y + y) * image_width + r.x) * 4, value, r.w);
		y++;
	}
}

void	ft_clear_dirty_cameras(t_data *d)
{
	int			i;
	t_camera	*cam;
	t_rect		rect;

	i = 0;
	while (i < d->scene->num_cameras)
	{
		cam = &d->scene->cameras[i];
		if (cam->dirty)
		{
			rect = cam->rect;
			ft_memset_rect(d->image.ray_targets, WIDTH_WIN, rect,
				SELECTED_NONE);
			rect.x *= 4;
			rect.w *= 4;
			ft_memset_rect(d->image.current_frame, WIDTH_WIN * 4, rect, 0);
			cam->dirty = 0;
			cam->cache_frame = 1;
			cam->frame_count = 0.0f;
		}
		i++;
	}
}

void	ft_prepare_cache_frame(t_data *d)
{
	int			i;
	t_camera	*cam;
	t_rect		rect;

	i = 0;
	while (i < d->scene->num_cameras)
	{
		cam = &d->scene->cameras[i];
		if (cam->frame_count == 1.0f && cam->cache_frame == 1)
		{
			rect = cam->rect;
			cam->frame_count = 0.0f;
			cam->cache_frame = 2;
			rect.x *= 4;
			rect.w *= 4;
			ft_memset_rect(d->image.current_frame, WIDTH_WIN * 4, rect, 0);
		}
		else if (cam->cache_frame == 2)
			cam->cache_frame = 0;
		i++;
	}
}
