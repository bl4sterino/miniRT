/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:35:52 by pberne            #+#    #+#             */
/*   Updated: 2026/01/25 21:26:39 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/* used for debugging, displays both objects and bvh hits as heatmap 
	NO DEPTH TEST */
t_v3d ft_shoot_ray_bvh(t_ray ray, t_scene *scene)
{
    t_bvh_node  *stack[64];
    int         stack_ptr = 0;
    int         nodes_traversed = 0;
    t_bvh_node  *current;
    stack[stack_ptr++] = scene->bvh_root;
    
    while (stack_ptr > 0)
    {
        current = stack[--stack_ptr];
		double t = ft_bounds_collision(ray, current->bounds);
        if (t != -1.0)
        {
			nodes_traversed++;
            if (current->num_obj == 0)
            {
                stack[stack_ptr++] = current->right;
                stack[stack_ptr++] = current->left;
            }
			else
			{
				t_object obj = scene->objects[current->start];
				if (ft_sphere_collision(ray, obj.object.as_sphere) > 0)
					return (obj.object.as_sphere.color);
				// Check for collisions with the leaf objects
			}
        }
    }
    float t = (float)nodes_traversed / (scene->bvh_nodes_count * 0.5);
    return ((t_v3d){t, t, t});
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
			if (DISPLAY_BVH)
				ray_result = ft_shoot_ray_bvh(ray, (d->scene));
			else
				ray_result = (t_v3d){0.1, 0.1, 0.1}; // True ray here
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
