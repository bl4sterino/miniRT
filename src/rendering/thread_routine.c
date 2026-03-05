/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:35:52 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 18:37:32 by pberne           ###   ########.fr       */
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
	return (context);
}

t_v3f	ft_get_viewport_target(t_data *d, t_thread_render_context c)
{
	return (ft_v3f_add(d->viewport.top_left,
			ft_v3f_add(ft_v3f_scale(d->viewport.x_delta, (float)c.pixel.x),
				ft_v3f_scale(d->viewport.y_delta, (float)c.pixel.y))));
}

void	ft_thread_render_function(t_data *d, t_render_task task)
{
	t_thread_render_context	context;
	t_out_buffer			out_buffer;
	t_v3f					hit_color;

	context = ft_setup_thread_render_data(d, task);
	while (++context.pixel.y < task.y_end)
	{
		context.pixel.x = task.x_start - 1;
		while (++context.pixel.x < task.x_end)
		{
			context.target = ft_get_viewport_target(d, context);
			context.ray = ft_setup_ray_target(context.ray, context.target,
					d->ray_bounces);
			if (d->render_mode != RENDER_BVH)
			{
				hit_color = ft_get_pixel_color(context.ray, d->scene,
						&out_buffer);
				if (d->render_mode == RENDER_DEFAULT)
					ft_add_pixel_to_accumulated_image(d, context.pixel,
						hit_color);
				else if (d->render_mode == RENDER_NORMALS)
				{
					out_buffer.hit_normal = ft_v3f_add(ft_v3f_scale(out_buffer.hit_normal, 0.5f),
							(t_v3f){{0.5f, 0.5f, 0.5f}});
					ft_add_pixel_to_accumulated_image(d, context.pixel,
						out_buffer.hit_normal);
				}
			}
			else
				ft_add_pixel_to_accumulated_image(d, context.pixel,
					ft_shoot_ray_bvh_debug(context.ray, d->scene));
			context.target = ft_v3f_add(context.target, d->viewport.x_delta);
		}
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
