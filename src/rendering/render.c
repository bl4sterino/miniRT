/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:52:25 by pberne            #+#    #+#             */
/*   Updated: 2026/04/06 21:00:36 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// FIXME: do multiple cameras simultaneously
void	ft_create_tasks_and_wait_for_completion(t_data *d)
{
	pthread_mutex_lock(&d->threads_data.task_mutex);
	d->threads_data.finished_lines = 0;
	d->threads_data.current_cam = 0;
	while (d->threads_data.current_cam < d->scene->num_cameras)
	{
		d->threads_data.current_line = 0;
		pthread_cond_broadcast(&d->threads_data.task_cond);
		while (d->threads_data.finished_lines < d->scene->cameras[d->threads_data.current_cam].rect.h)
			pthread_cond_wait(&d->threads_data.done_cond,
				&d->threads_data.task_mutex);
		pthread_mutex_unlock(&d->threads_data.task_mutex);
		d->threads_data.current_cam++;
	}
}

void	ft_render_preprocess_2(t_data *d)
{
	if (d->dirty_frame)
	{
		d->dirty_frame = 0;
		d->cache_frame = 1;
		d->frame_count = 0.0f;
		ft_memset_int(d->image.current_frame, 0, SCREEN_SIZE * 4);
		ft_memset_int(d->image.ray_targets, SELECTED_NONE, SCREEN_SIZE);
	}
	if (d->frame_count == 1.0f && d->cache_frame == 1)
	{
		d->frame_count = 0.0f;
		d->cache_frame = 2;
		ft_memset_int(d->image.current_frame, 0, SCREEN_SIZE * 4);
	}
	else if (d->cache_frame == 2)
		d->cache_frame = 0;
}

void	ft_render_preprocess(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->scene->num_objects)
	{
		d->scene->objects[i].material.reflectiveness_rand = fast_rand();
		i++;
	}
	i = 0;
	while (i < d->scene->num_planes)
	{
		d->scene->planes[i].material.reflectiveness_rand = fast_rand();
		i++;
	}
	ft_render_preprocess_2(d);
}

void	ft_render(t_data *d)
{
	int	i;

	ft_clock_start(clock_render);
	if (d->dirty_frame)
		d->ray_bounces = ft_min(1, d->target_ray_bounces);
	else if (d->ray_bounces != d->target_ray_bounces)
		d->ray_bounces = d->target_ray_bounces;
	ft_render_preprocess(d);
	i = 0;
	while (i < d->scene->num_cameras)
	{
		d->viewports[i] = ft_get_viewport(d->scene->cameras[i], d);
		i++;
	}
	ft_create_tasks_and_wait_for_completion(d);
	ft_clock_set(clock_render);
}
