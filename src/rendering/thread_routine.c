/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:35:52 by pberne            #+#    #+#             */
/*   Updated: 2026/04/06 18:52:38 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_wait_for_task_or_die_trying(t_data *d, t_render_task *task)
{
	pthread_mutex_lock(&d->threads_data.task_mutex);
	while (d->threads_data.current_line == HEIGHT_WIN)
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
	pthread_mutex_unlock(&d->threads_data.task_mutex);
	return (1);
}

t_thread_render_context	ft_setup_thread_render_data(t_data *d,
		t_render_task task)
{
	t_thread_render_context	context;

	ft_bzero(&context, sizeof(t_thread_render_context));
	context.ray.origin = d->scene->camera.position;
	context.pixel.y = task.y;
	context.pixel.x = 0;
	return (context);
}

static inline void	ft_render_pixel_classic(t_data *d,
		t_thread_render_context *c)
{
	t_v3f	hit_color;

	hit_color = ft_get_pixel_color(c->ray, d->scene, &c->out,
			d->image.ray_targets[c->index]);
	if (d->render_mode == RENDER_DEFAULT)
		ft_add_pixel_to_accumulated_image(d, c->index, hit_color);
	else if (d->render_mode == RENDER_NORMALS)
	{
		c->out.hit_normal = ft_v3f_add(ft_v3f_scale(c->out.hit_normal, 0.5f),
				(t_v3f){{0.5f, 0.5f, 0.5f}});
		ft_add_pixel_to_accumulated_image(d, c->index, c->out.hit_normal);
	}
}

void	ft_thread_render_function(t_data *d, t_render_task task)
{
	t_thread_render_context	c;

	c = ft_setup_thread_render_data(d, task);
	c.pixel.x = 0;
	while (c.pixel.x < WIDTH_WIN)
	{
		c.index = c.pixel.y * WIDTH_WIN + c.pixel.x;
		if (d->cache_frame == 2)
			d->image.ray_targets[c.index] = ft_cache_ray_target(d, &c);
		c.target = ft_get_viewport_target(d, c);
		c.ray = ft_setup_ray_target(c.ray, c.target, d->ray_bounces, 0);
		if (d->render_mode != RENDER_BVH)
			ft_render_pixel_classic(d, &c);
		else
			ft_add_pixel_to_accumulated_image(d, c.index,
				ft_shoot_ray_bvh_debug(c.ray, d->scene));
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
		if (d->threads_data.finished_lines == HEIGHT_WIN)
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
