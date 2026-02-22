/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:52:25 by pberne            #+#    #+#             */
/*   Updated: 2026/02/22 19:03:46 by pberne           ###   ########.fr       */
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

void	ft_render(t_data *d)
{
	ft_clock_start(clock_render);
	if (d->dirty_frame)
	{
		ft_memset_int(d->image.accumulated_addr, 0, (sizeof(double)
				/ sizeof(int)) * WIDTH_WIN * HEIGHT_WIN * 3);
		d->frame_count = 0;
		d->dirty_frame = 0;
		d->ray_bounces = ft_min(1, d->target_ray_bounces);
	}
	else if (d->ray_bounces != d->target_ray_bounces)
	{
		ft_memset_int(d->image.accumulated_addr, 0, (sizeof(double)
				/ sizeof(int)) * WIDTH_WIN * HEIGHT_WIN * 3);
		d->ray_bounces = d->target_ray_bounces;
	}
	ft_create_tasks_and_wait_for_completion(d);
	ft_clock_set(clock_render);
}

