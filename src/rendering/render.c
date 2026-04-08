/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:52:25 by pberne            #+#    #+#             */
/*   Updated: 2026/04/08 12:34:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// FIXME: do multiple cameras simultaneously
void	ft_create_tasks_and_wait_for_completion(t_data *d)
{
	pthread_mutex_lock(&d->threads_data.task_mutex);
	d->threads_data.current_cam = 0;
	while (d->threads_data.current_cam < d->scene->num_cameras)
	{
		d->threads_data.finished_lines = 0;
		d->threads_data.current_line = 0;
		pthread_cond_broadcast(&d->threads_data.task_cond);
		while (d->threads_data.finished_lines
			< d->scene->cameras[d->threads_data.current_cam].rect.h)
			pthread_cond_wait(&d->threads_data.done_cond,
				&d->threads_data.task_mutex);
		d->threads_data.current_cam++;
	}
	pthread_mutex_unlock(&d->threads_data.task_mutex);
}

void	ft_render_preprocess_2(t_data *d)
{
	if (d->dirty_frame)
		ft_set_all_cameras_dirty(d);
	ft_clear_dirty_cameras(d);
	ft_prepare_cache_frame(d);
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
	i = 0;
	while (i < d->scene->num_cameras)
	{
		d->viewports[i] = ft_get_viewport(d->scene->cameras[i], d);
		i++;
	}
	ft_render_preprocess(d);
	ft_create_tasks_and_wait_for_completion(d);
	ft_clock_set(clock_render);
}
