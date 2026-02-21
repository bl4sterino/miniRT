/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:52:25 by pberne            #+#    #+#             */
/*   Updated: 2026/02/21 16:23:02 by pberne           ###   ########.fr       */
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

void	ft_setup_tasks(t_data *d)
{
	ft_clock_start(clock_render);
	if (d->dirty_frame)
	{
		ft_memset_int(d->image.accumulated_addr, 0, (sizeof(double)
				/ sizeof(int)) * WIDTH_WIN * HEIGHT_WIN * 3);
		d->frame_count = 0;
		d->dirty_frame = 0;
		d->ray_bounces = 0;
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

void	ft_push_accumulated_data_to_image(t_data *d)
{
	t_v2i	pos;
	t_v3d	color;
	int		i;

	i = 0;
	d->frame_count += 1.0;
	pos.y = 0;
	while (pos.y < HEIGHT_WIN)
	{
		pos.x = 0;
		while (pos.x < WIDTH_WIN)
		{
			color.x = d->image.accumulated_addr[i];
			color.y = d->image.accumulated_addr[i + 1];
			color.z = d->image.accumulated_addr[i + 2];
			color = ft_v3d_div(color, d->frame_count);
			color = ft_v3d_min(color, (t_v3d){{1.0, 1.0, 1.0}});
			ft_put_pxl(d->image.addr, pos, ft_v3d_to_int_color(color));
			pos.x++;
			i += 3;
		}
		pos.y++;
	}
}
