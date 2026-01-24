/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:35:52 by pberne            #+#    #+#             */
/*   Updated: 2026/01/24 15:05:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_get_ray_color(t_ray ray, t_scene *scene)
{
	t_sphere	*spheres;
	int			i;
	double		bestdist;
	double		dist;
	int			best_i;

	spheres = scene->spheres;
	i = 0;
	bestdist = INFINITY;
	best_i = -1;
	while (i < scene->num_spheres)
	{
		dist = ft_sphere_collision(ray, spheres[i]);
		if (dist >= 0 && dist < bestdist)
		{
			bestdist = dist;
			best_i = i;
		}
		i++;
	}
	if (best_i >= 0)
		return (ft_v3d_to_int_color(scene->spheres[best_i].color));
	return (0);
}

int	ft_wait_for_task_or_die_trying(t_data *d, t_render_task *task)
{
	t_render_task	new_task;

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
	new_task = d->threads_data.tasks[d->threads_data.tasks_count - 1];
	d->threads_data.tasks_count -= 1;
	*task = new_task;
	pthread_mutex_unlock(&d->threads_data.task_mutex);
	return (1);
}

void	ft_thread_render_function(t_data *d, t_render_task task)
{
	t_v2i	pixel;
	t_ray	ray;
	t_v3d	target;
	t_v3d	y_target;

	ray.origin = d->scene->camera.position;
	pixel.y = task.line_start;
	y_target = ft_v3d_add(d->viewport.top_left,
			ft_v3d_scale(d->viewport.y_delta, pixel.y));
	while (pixel.y < task.line_end)
	{
		pixel.x = 0;
		target = y_target;
		while (pixel.x < WIDTH_WIN)
		{
			ray.direction = ft_v3d_sub(target, ray.origin);
			ft_put_pxl(d->image.addr, pixel, ft_get_ray_color(ray, (d->scene)));
			target = ft_v3d_add(target, d->viewport.x_delta);
			pixel.x++;
		}
		y_target = ft_v3d_add(y_target, d->viewport.y_delta);
		pixel.y++;
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
		if (d->threads_data.finished_tasks == d->threads_data.count)
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
