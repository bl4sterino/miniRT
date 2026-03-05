/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 10:33:38 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 18:23:41 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_render_task	ft_get_task_tile(int x, int y)
{
	t_render_task	task;

	task.y_start = y * TASK_TILE_SIZE;
	if (y + 1 == HEIGHT_WIN / TASK_TILE_SIZE)
		task.y_end = HEIGHT_WIN;
	else
		task.y_end = task.y_start + TASK_TILE_SIZE;
	task.x_start = x * TASK_TILE_SIZE;
	if (x + 1 == WIDTH_WIN / TASK_TILE_SIZE)
		task.x_end = WIDTH_WIN;
	else
		task.x_end = task.x_start + TASK_TILE_SIZE;
	return (task);
}

void	ft_create_tasks_tile(t_data *d)
{
	int	i;
	int	x;
	int	y;

	x = 0;
	y = -1;
	i = 0;
	d->threads_data.tasks_total_count = (WIDTH_WIN / TASK_TILE_SIZE)
		* (HEIGHT_WIN / TASK_TILE_SIZE);
	d->threads_data.tasks = ft_malloc(sizeof(t_render_task)
			* d->threads_data.tasks_total_count);
	while (++y < HEIGHT_WIN / TASK_TILE_SIZE)
	{
		x = 0;
		while (x < WIDTH_WIN / TASK_TILE_SIZE)
		{
			d->threads_data.tasks[i] = ft_get_task_tile(x, y);
			x++;
			i++;
		}
	}
}

t_render_task	ft_get_task_line(int index)
{
	t_render_task	task;

	index *= TASK_LINE_SIZE;
	task.y_start = index / WIDTH_WIN;
	task.x_start = index % WIDTH_WIN;
	task.y_end = task.y_start + 1;
	task.x_end = task.x_start + TASK_LINE_SIZE;
	return (task);
}

void	ft_create_task_line(t_data *d)
{
	int	i;

	d->threads_data.tasks_total_count = SCREEN_SIZE / TASK_LINE_SIZE
		+ (SCREEN_SIZE % TASK_LINE_SIZE != 0);
	d->threads_data.tasks = ft_malloc(sizeof(t_render_task)
			* d->threads_data.tasks_total_count);
	i = 0;
	while (i < d->threads_data.tasks_total_count)
	{
		d->threads_data.tasks[i] = ft_get_task_line(i);
		i++;
	}
}

void	ft_task_builder(t_data *d)
{
	if (d->threads_data.task_mode == TASK_MODE_UNSET)
		d->threads_data.task_mode = TASK_MODE_LINE;
	if (d->threads_data.task_mode == TASK_MODE_TILE)
		ft_create_tasks_tile(d);
	else
		ft_create_task_line(d);
}
