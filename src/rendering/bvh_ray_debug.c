/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_ray_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:33:14 by pberne            #+#    #+#             */
/*   Updated: 2026/03/02 21:46:31 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void	ft_check_objects_collisions(t_ray ray, t_scene *scene,
		t_bvh_context_debug *context)
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
		else if (obj.type == object_type_cylinder)
			dist = ft_cylinder_collision(ray, obj.object.as_cylinder);
		if (dist < context->best_dist)
		{
			context->best_dist = dist;
			context->best_index = i;
		}
		i++;
	}
}

static inline void	ft_add_branches_to_stack(t_ray *ray,
		t_bvh_context_debug *context)
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

t_v3f	ft_shoot_ray_bvh_debug(t_ray ray, t_scene *scene)
{
	t_bvh_context_debug	context;

	context.best_dist = INFINITY;
	context.best_index = -1;
	context.stack_ptr = 0;
	context.nodes_traversed = 0;
	context.stack[context.stack_ptr++] = scene->bvh_root;
	while (context.stack_ptr > 0)
	{
		context.current = &scene->bvh_nodes[context.stack[--context.stack_ptr]];
		context.t = ft_bounds_collision(ray, context.current->bounds);
		if (context.t >= context.best_dist)
			continue ;
		context.nodes_traversed++;
		if (context.current->num_obj == 0)
			ft_add_branches_to_stack(&ray, &context);
		else
			ft_check_objects_collisions(ray, scene, &context);
	}
	(void)context.best_index;
	context.t = fmin((float)context.nodes_traversed / 64, 1.0);
	return ((t_v3f){{(float)context.t, (float)context.t, (float)context.t}});
}


