/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:35:52 by pberne            #+#    #+#             */
/*   Updated: 2026/04/10 17:42:16 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_wait_for_task_or_die_trying(t_data *d, t_render_task *task)
{
	pthread_mutex_lock(&d->threads_data.task_mutex);
	while (d->threads_data.current_cam >= d->scene->num_cameras
		|| d->threads_data.current_line
		>= d->scene->cameras[d->threads_data.current_cam].rect.h)
	{
		pthread_cond_wait(&d->threads_data.task_cond,
			&d->threads_data.task_mutex);
		if (d->threads_data.run_threads == -1)
		{
			pthread_mutex_unlock(&d->threads_data.task_mutex);
			return (0);
		}
	}
	task->y = d->threads_data.current_line++;
	task->cam_idx = d->threads_data.current_cam;
	pthread_mutex_unlock(&d->threads_data.task_mutex);
	return (1);
}

t_thread_render_context	ft_setup_thread_render_data(t_data *d,
		t_render_task task)
{
	t_thread_render_context	context;

	ft_bzero(&context, sizeof(t_thread_render_context));
	context.pixel.y = task.y;
	context.pixel.x = 0;
	context.cam = d->scene->cameras[task.cam_idx];
	context.ray.origin = context.cam.position;
	context.vp = d->viewports[task.cam_idx];
	return (context);
}

void	ft_thread_render_function(t_data *d, t_render_task task)
{
	t_thread_render_context	c;

	c = ft_setup_thread_render_data(d, task);
	while (c.pixel.x < c.cam.rect.w)
	{
		c.index = (c.pixel.y + c.cam.rect.y) * WIDTH_WIN + (c.pixel.x
				+ c.cam.rect.x);
		if ((c.cam.cache_frame == 2 || c.cam.render_mode == RENDER_RAY_TARGETS)
			&& c.cam.stereo == 0)
			d->image.ray_targets[c.index] = ft_cache_ray_target(d, &c.vp, &c);
		if (!c.cam.stereo)
			ft_render_mode_basic(d, &c, task.cam_idx);
		else
			ft_render_mode_stereo(d, &c, task.cam_idx);
		c.pixel.x++;
	}
}

void	*ft_thread_loop(void *arg)
{
	t_data			*d;
	t_render_task	task;

	d = (t_data *)arg;
	while (1)
	{
		if (!ft_wait_for_task_or_die_trying(d, &task))
			return (0);
		ft_thread_render_function(d, task);
		pthread_mutex_lock(&d->threads_data.task_mutex);
		d->threads_data.finished_lines++;
		if (d->threads_data.finished_lines
			== d->scene->cameras[d->threads_data.current_cam].rect.h)
			pthread_cond_signal(&d->threads_data.done_cond);
		if (d->threads_data.run_threads == -1)
		{
			pthread_mutex_unlock(&d->threads_data.task_mutex);
			return (0);
		}
		pthread_mutex_unlock(&d->threads_data.task_mutex);
	}
	return (0);
}
