/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:43:04 by pberne            #+#    #+#             */
/*   Updated: 2026/04/02 17:40:33 by pberne           ###   ########.fr       */
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

static void	ft_shoot_ray_obj_init(t_bvh_context *c, float max_dist,
		int root)
{
	c->best_dist = max_dist;
	c->best_index = -1;
	c->stack_ptr = 0;
	c->node_idx = root;
}

float	ft_shoot_ray_against_objects(t_ray ray, float max_dist, t_scene *scene,
		int *hit)
{
	t_bvh_context	c;

	ft_shoot_ray_obj_init(&c, max_dist, scene->bvh_root);
	while (1 && scene->bvh_root >= 0)
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
		ft_intersect_aabb_x2_fast(ray, &c.node->bounds2x, c.dist);
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
	if (best_dist < FT_INFINITY)
		*hit = -(best_index + 1);
	return (best_dist);
}

float	ft_shoot_ray(t_ray ray, t_scene *scene, int *hit)
{
	float	plane_dist;
	float	distance;

	plane_dist = ft_shoot_ray_against_planes(ray, FT_INFINITY, scene, hit);
	distance = ft_shoot_ray_against_objects(ray, plane_dist, scene, hit);
	if (plane_dist <= distance && plane_dist != FT_INFINITY)
		return (plane_dist);
	return (distance);
}
