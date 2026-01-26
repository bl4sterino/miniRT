/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:52:25 by pberne            #+#    #+#             */
/*   Updated: 2026/01/26 17:13:46 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_build_task(t_data *d, int x, int y, int i)
{
	d->threads_data.tasks[i].y_start = y * TILE_SIZE;
	if (y + 1 == HEIGHT_WIN / TILE_SIZE)
		d->threads_data.tasks[i].y_end = HEIGHT_WIN - 1;
	else
		d->threads_data.tasks[i].y_end = d->threads_data.tasks[i].y_start
			+ TILE_SIZE;
	d->threads_data.tasks[i].x_start = x * TILE_SIZE;
	d->threads_data.tasks[i].x_end = d->threads_data.tasks[i].x_start
		+ TILE_SIZE;
}

void	ft_setup_tasks(t_data *d)
{
	int	i;
	int	x;
	int	y;

	x = 0;
	y = -1;
	i = 0;
	pthread_mutex_lock(&d->threads_data.task_mutex);
	d->threads_data.finished_tasks = 0;
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
	d->threads_data.tasks_count = i;
	pthread_cond_broadcast(&d->threads_data.task_cond);
	while (d->threads_data.finished_tasks < d->threads_data.tasks_count)
		pthread_cond_wait(&d->threads_data.done_cond,
			&d->threads_data.task_mutex);
	pthread_mutex_unlock(&d->threads_data.task_mutex);
}

void	ft_render(t_data *d)
{
	d->viewport = ft_get_viewport(d->scene->camera);
	ft_clock_start(clock_render);
	ft_setup_tasks(d);
	ft_clock_set(clock_render);
}
