/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:43:04 by pberne            #+#    #+#             */
/*   Updated: 2026/01/30 12:19:29 by pberne           ###   ########.fr       */
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
		else if (obj.type == object_type_cylinder)
			dist = ft_cylinder_collision(ray, obj.object.as_cylinder);
		else if (obj.type == object_type_quad)
			dist = ft_quad_collision(ray, obj.object.as_quad);
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

double	ft_shoot_ray_against_objects(t_ray ray, double max_dist, t_scene *scene,
		int *hit)
{
	t_bvh_context	context;

	context.best_dist = max_dist;
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
	if (context.best_dist < max_dist)
		*hit = context.best_index;
	return (context.best_dist);
}

double	ft_shoot_ray_against_planes(t_ray ray, double max_dist, t_scene *scene,
		int *hit)
{
	double	dist;
	int		best_index;
	double	best_dist;
	int		i;

	best_dist = max_dist;
	i = 0;
	best_index = -1;
	while (i < scene->num_planes)
	{
		dist = ft_plane_collision(ray, scene->planes[i].object.as_plane);
		if (dist < best_dist)
		{
			best_index = i;
			best_dist = dist;
		}
		i++;
	}
	if (best_dist < INFINITY)
		*hit = -(best_index + 1);
	return (best_dist);
}

double	ft_shoot_ray(t_ray ray, t_scene *scene, int *hit)
{
	double	plane_dist;
	double	distance;

	plane_dist = ft_shoot_ray_against_planes(ray, INFINITY, scene, hit);
	distance = ft_shoot_ray_against_objects(ray, plane_dist, scene, hit);
	if (plane_dist <= distance && plane_dist != INFINITY)
		return (plane_dist);
	return (distance);
}
