/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:43:04 by pberne            #+#    #+#             */
/*   Updated: 2026/01/27 18:13:13 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void	ft_check_objects_collisions(t_ray ray, t_scene *scene,
		t_bvh_context *context)
{
	int			i;
	int			end;
	t_object	obj;
	double		dist;

	dist = INFINITY;
	i = context->current->start;
	end = i + context->current->num_obj;
	while (i < end)
	{
		obj = scene->objects[i];
		if (obj.type == object_type_sphere)
			dist = ft_sphere_collision(ray, obj.object.as_sphere);
		if (dist < context->best_dist)
		{
			context->best_dist = dist;
			context->best_index = i;
		}
		i++;
	}
}

static inline void	ft_add_branches_to_stack(t_ray *ray, t_bvh_context *context)
{
	if (ray->direction.v[context->current->split_axis] < 0)
	{
		context->stack[context->stack_ptr++] = context->current->left;
		context->stack[context->stack_ptr++] = context->current->right;
	}
	else
	{
		context->stack[context->stack_ptr++] = context->current->right;
		context->stack[context->stack_ptr++] = context->current->left;
	}
}

double	ft_shoot_ray(t_ray ray, t_scene *scene, int *hit)
{
	t_bvh_context	context;

	context.best_dist = INFINITY;
	context.best_index = -1;
	context.stack_ptr = 0;
	context.stack[context.stack_ptr++] = scene->bvh_root;
	while (context.stack_ptr > 0)
	{
		context.current = &scene->bvh_nodes[context.stack[--context.stack_ptr]];
		context.t = ft_bounds_collision(ray, context.current->bounds);
		if (context.t >= context.best_dist)
			continue ;
		if (context.current->num_obj == 0)
			ft_add_branches_to_stack(&ray, &context);
		else
			ft_check_objects_collisions(ray, scene, &context);
	}
	if (context.best_dist < INFINITY)
		*hit = context.best_index;
	return (context.best_dist);
}

/* this is where the ray bounces and split are processed
	handle reflection / transparency here */
t_v3d	ft_get_pixel_color(t_ray ray, t_scene *scene)
{
	int		hit;
	double	distance;

	distance = ft_shoot_ray(ray, (scene), &hit);
	if (distance < INFINITY)
		return (scene->objects[hit].object.as_sphere.color);
	else
		return ((t_v3d){{0.05, 0.05, 0.05}});
}
