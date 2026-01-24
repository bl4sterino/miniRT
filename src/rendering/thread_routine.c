/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:35:52 by pberne            #+#    #+#             */
/*   Updated: 2026/01/24 18:32:53 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_ray_bounds_check(t_ray ray, t_bounds b)
{
	float	t1;
	float	t2;
	float	tmin;
	float	tmax;

	t1 = (b.min.x - ray.origin.x) * ray.inv_dir.x;
	t2 = (b.max.x - ray.origin.x) * ray.inv_dir.x;
	tmin = fmin(t1, t2);
	tmax = fmax(t1, t2);
	t1 = (b.min.y - ray.origin.y) * ray.inv_dir.y;
	t2 = (b.max.y - ray.origin.y) * ray.inv_dir.y;
	tmin = fmax(tmin, fmin(t1, t2));
	tmax = fmin(tmax, fmax(t1, t2));
	t1 = (b.min.z - ray.origin.z) * ray.inv_dir.z;
	t2 = (b.max.z - ray.origin.z) * ray.inv_dir.z;
	tmin = fmax(tmin, fmin(t1, t2));
	tmax = fmin(tmax, fmax(t1, t2));
	return (tmax >= fmax(0.0f, tmin));
}

t_v3d	ft_shoot_ray(t_ray ray, t_scene *scene)
{
	t_bvh_node	*stack[64];
	int			stack_ptr;
	t_bvh_node	*current;

	stack_ptr = 0;
	stack[stack_ptr++] = scene->bvh_root;
	while (stack_ptr > 0)
	{
		current = stack[--stack_ptr];
		if (!ft_ray_bounds_check(ray, current->bounds))
			continue ;
		if (current->num_obj > 0)
		{
			// Final object collision check
			return ((t_v3d){1, 1, 1});
		}
		else
		{
			// maybe push the closest one last
			stack[stack_ptr++] = current->right;
			stack[stack_ptr++] = current->left;
		}
	}
	return (scene->ambient_light.color);
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
	t_v3d	ray_result;

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
			ray.inv_dir = ft_v3d_div_safe((t_v3d){1, 1, 1}, ray.direction);
			ray_result = ft_shoot_ray(ray, (d->scene));
			ft_put_pxl(d->image.addr, pixel, ft_v3d_to_int_color(ray_result));
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

/*int	ft_get_ray_color(t_ray ray, t_scene *scene)
{
	t_object	*objects;
	int			i;
	double		bestdist;
	double		dist;
	int			best_i;

	objects = scene->objects;
	i = 0;
	bestdist = INFINITY;
	best_i = -1;
	while (i < scene->num_objects)
	{
		if (objects[i].type == object_type_sphere)
			dist = ft_sphere_collision(ray, objects[i].object.as_sphere);
		if (dist >= 0 && dist < bestdist)
		{
			bestdist = dist;
			best_i = i;
		}
		i++;
	}
	if (best_i >= 0)
		return (ft_v3d_to_int_color(objects[best_i].object.as_sphere.color));
	return (0);
}*/