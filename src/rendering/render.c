/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:52:25 by pberne            #+#    #+#             */
/*   Updated: 2026/01/24 14:57:43 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_build_task(t_data *d, int i, int count)
{
	int	interval;

	interval = HEIGHT_WIN / d->threads_data.count;
	d->threads_data.tasks[i].line_start = i * interval;
	if (i == count - 1)
		d->threads_data.tasks[i].line_end = HEIGHT_WIN;
	else
		d->threads_data.tasks[i].line_end = (i + 1) * interval;
}

void	ft_setup_tasks(t_data *d)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&d->threads_data.task_mutex);
	d->threads_data.finished_tasks = 0;
	while (i < d->threads_data.count)
	{
		ft_build_task(d, i, d->threads_data.count);
		i++;
	}
	d->threads_data.tasks_count = d->threads_data.count;
	pthread_cond_broadcast(&d->threads_data.task_cond);
	while (d->threads_data.finished_tasks < d->threads_data.count)
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
