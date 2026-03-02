/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:52:25 by pberne            #+#    #+#             */
/*   Updated: 2026/03/02 14:56:50 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_build_task(t_data *d, int x, int y, int i)
{
	d->threads_data.tasks[i].y_start = y * TILE_SIZE;
	if (y + 1 == HEIGHT_WIN / TILE_SIZE)
		d->threads_data.tasks[i].y_end = HEIGHT_WIN;
	else
		d->threads_data.tasks[i].y_end = d->threads_data.tasks[i].y_start
			+ TILE_SIZE;
	d->threads_data.tasks[i].x_start = x * TILE_SIZE;
	if (x + 1 == WIDTH_WIN / TILE_SIZE)
		d->threads_data.tasks[i].x_end = WIDTH_WIN;
	else
		d->threads_data.tasks[i].x_end = d->threads_data.tasks[i].x_start
			+ TILE_SIZE;
}

void	ft_create_task_loop(t_data *d)
{
	static int	done = 0;
	int			i;
	int			x;
	int			y;

	x = 0;
	y = -1;
	i = 0;
	if (done == 0)
	{
		while (++y < HEIGHT_WIN / TILE_SIZE)
		{
			x = 0;
			while (x < WIDTH_WIN / TILE_SIZE)
			{
				ft_build_task(d, x, y, i);
				x++;
				i++;
			}
		}
		done = 1;
	}
}

void	ft_create_tasks_and_wait_for_completion(t_data *d)
{
	ft_create_task_loop(d);
	pthread_mutex_lock(&d->threads_data.task_mutex);
	d->threads_data.finished_tasks = 0;
	d->threads_data.tasks_count = d->threads_data.tasks_total_count;
	pthread_cond_broadcast(&d->threads_data.task_cond);
	while (d->threads_data.finished_tasks < d->threads_data.tasks_count)
		pthread_cond_wait(&d->threads_data.done_cond,
			&d->threads_data.task_mutex);
	pthread_mutex_unlock(&d->threads_data.task_mutex);
}

#ifndef OPENCL_BONK

/* this sucks for big scene but we need it for current frame blur consistency
the object is either reflecting or not  during the current frame, not per pixel */
void ft_render_preprocess(t_data *d)
{
	int i = 0;
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
}

#else

void ft_render_preprocess(t_data *d)
{
	int i = 0;
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

	if (d->dirty_frame)
	{
		d->dirty_frame = 0;
		d->frame_count = 0.0f;
		ft_memset_int(d->image.current_frame, 0, SCREEN_SIZE * 4);
	}
}

#endif

void	ft_render(t_data *d)
{
	ft_clock_start(clock_render);
	if (d->dirty_frame)
		d->ray_bounces = ft_min(1, d->target_ray_bounces);
	else if (d->ray_bounces != d->target_ray_bounces)
		d->ray_bounces = d->target_ray_bounces;
	ft_render_preprocess(d);
	ft_create_tasks_and_wait_for_completion(d);
	ft_clock_set(clock_render);
}
