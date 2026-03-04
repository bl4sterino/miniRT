/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:43:04 by pberne            #+#    #+#             */
/*   Updated: 2026/03/04 13:26:14 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline int	ft_push_next_node_to_stack(t_bvh_context *c)
{
	if (c->dist[0] < c->best_dist && c->dist[1] < c->best_dist)
	{
		if (c->dist[0] < c->dist[1])
		{
			c->stack[c->stack_ptr++] = c->r_idx;
			c->node_idx = c->l_idx;
		}
		else
		{
			c->stack[c->stack_ptr++] = c->l_idx;
			c->node_idx = c->r_idx;
		}
	}
	else if (c->dist[0] < c->best_dist)
		c->node_idx = c->l_idx;
	else if (c->dist[1] < c->best_dist)
		c->node_idx = c->r_idx;
	else
	{
		if (c->stack_ptr == 0)
			return (1);
		c->node_idx = c->stack[--c->stack_ptr];
	}
	return (0);
}

static void	ft_shoot_ray_obj_init(t_bvh_context *c, t_ray ray, float max_dist,
		int root)
{
	c->aabb_c.r_org[0] = _mm_set1_ps(ray.origin.x);
	c->aabb_c.r_org[1] = _mm_set1_ps(ray.origin.y);
	c->aabb_c.r_org[2] = _mm_set1_ps(ray.origin.z);
	c->aabb_c.r_inv[0] = _mm_set1_ps(ray.inv_dir.x);
	c->aabb_c.r_inv[1] = _mm_set1_ps(ray.inv_dir.y);
	c->aabb_c.r_inv[2] = _mm_set1_ps(ray.inv_dir.z);
	c->best_dist = max_dist;
	c->best_index = -1;
	c->stack_ptr = 0;
	c->node_idx = root;
}

float	ft_shoot_ray_against_objects(t_ray ray, float max_dist, t_scene *scene,
		int *hit)
{
	t_bvh_context	c;

	ft_shoot_ray_obj_init(&c, ray, max_dist, scene->bvh_root);
	while (1)
	{
		c.node = &scene->bvh_nodes[c.node_idx];
		if (c.node->left == -1)
		{
			ft_check_objects_collisions(ray, c.node->start, &c,
				&scene->objects[c.node->start]);
			if (c.stack_ptr == 0)
				break ;
			c.node_idx = c.stack[--c.stack_ptr];
			continue ;
		}
		c.l_idx = c.node->left;
		c.r_idx = c.node->right;
		ft_intersect_aabb_x2_fast(c.aabb_c, &scene->bvh_nodes[c.l_idx].bounds,
			&scene->bvh_nodes[c.r_idx].bounds, c.dist);
		if (ft_push_next_node_to_stack(&c))
			break ;
	}
	if (c.best_dist < max_dist)
		*hit = c.best_index;
	return (c.best_dist);
}

float	ft_shoot_ray_against_planes(t_ray ray, float max_dist, t_scene *scene,
		int *hit)
{
	float	dist;
	int		best_index;
	float	best_dist;
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

float	ft_shoot_ray(t_ray ray, t_scene *scene, int *hit)
{
	float	plane_dist;
	float	distance;

	plane_dist = ft_shoot_ray_against_planes(ray, INFINITY, scene, hit);
	distance = ft_shoot_ray_against_objects(ray, plane_dist, scene, hit);
	if (plane_dist <= distance && plane_dist != INFINITY)
		return (plane_dist);
	return (distance);
}

/*static inline void	ft_add_branches_to_stack(t_ray *ray,
		t_bvh_context *context)
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

float	ft_shoot_ray_against_objects(t_ray ray, float max_dist, t_scene *scene,
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
}*/
