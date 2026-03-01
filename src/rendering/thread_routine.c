/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:35:52 by pberne            #+#    #+#             */
/*   Updated: 2026/03/01 12:53:39 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_wait_for_task_or_die_trying(t_data *d, t_render_task *task)
{
	pthread_mutex_lock(&d->threads_data.task_mutex);
	while (d->threads_data.tasks_count == 0)
	{
		pthread_cond_wait(&d->threads_data.task_cond,
			&d->threads_data.task_mutex);
		if (d->threads_data.run_threads == -1)
		{
			pthread_mutex_unlock(&d->threads_data.task_mutex);
			return (0);
		}
	}
	*task = d->threads_data.tasks[d->threads_data.tasks_count - 1];
	d->threads_data.tasks_count -= 1;
	pthread_mutex_unlock(&d->threads_data.task_mutex);
	return (1);
}

t_thread_render_context	ft_setup_thread_render_data(t_data *d,
		t_render_task task)
{
	t_thread_render_context	context;

	ft_bzero(&context, sizeof(t_thread_render_context));
	context.ray.origin = d->scene->camera.position;
	context.pixel.y = task.y_start - 1;
	context.pixel.x = task.x_start - 1;
	context.y_target = ft_v3f_add(d->viewport.top_left,
			ft_v3f_scale(d->viewport.y_delta, context.pixel.y + 1));
	context.y_target = ft_v3f_add(context.y_target,
			ft_v3f_scale(d->viewport.x_delta, context.pixel.x));
	return (context);
}

void	ft_thread_render_function(t_data *d, t_render_task task)
{
	t_thread_render_context	context;
	t_v3f hit_normal;
	t_v3f hit_pos;

	context = ft_setup_thread_render_data(d, task);
	while (++context.pixel.y < task.y_end)
	{
		context.pixel.x = task.x_start - 1;
		context.target = context.y_target;
		while (++context.pixel.x < task.x_end)
		{
			context.ray = ft_setup_ray_target(context.ray, context.target,
					d->ray_bounces);
			if (d->render_mode != RENDER_BVH)
			{
				ft_add_pixel_to_accumulated_image(d, context.pixel,
					ft_get_pixel_color(context.ray, d->scene, &hit_normal, &hit_pos), hit_normal, hit_pos);
			}
			else
				ft_add_pixel_to_accumulated_image(d, context.pixel,
					ft_shoot_ray_bvh_debug(context.ray, d->scene), hit_normal, hit_pos);
			context.target = ft_v3f_add(context.target, d->viewport.x_delta);
		}
		context.y_target = ft_v3f_add(context.y_target, d->viewport.y_delta);
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
		d->threads_data.finished_tasks += 1;
		if (d->threads_data.finished_tasks == d->threads_data.tasks_total_count)
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
