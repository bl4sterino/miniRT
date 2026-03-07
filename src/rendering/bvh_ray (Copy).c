/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:43:04 by pberne            #+#    #+#             */
/*   Updated: 2026/03/06 19:41:13 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// static inline int	ft_push_next_node_to_stack(t_bvh_context *c)
// {
// 	if (c->dist[0] < c->best_dist && c->dist[1] < c->best_dist)
// 	{
// 		if (c->dist[0] < c->dist[1])
// 		{
// 			c->stack[c->stack_ptr++] = c->r_idx;
// 			c->node_idx = c->l_idx;
// 		}
// 		else
// 		{
// 			c->stack[c->stack_ptr++] = c->l_idx;
// 			c->node_idx = c->r_idx;
// 		}
// 	}
// 	else if (c->dist[0] < c->best_dist)
// 		c->node_idx = c->l_idx;
// 	else if (c->dist[1] < c->best_dist)
// 		c->node_idx = c->r_idx;
// 	else
// 	{
// 		if (c->stack_ptr == 0)
// 			return (1);
// 		c->node_idx = c->stack[--c->stack_ptr];
// 	}
// 	return (0);
// }

static inline void	ft_push_next_node_to_stack(t_bvh_context *c)
{
	// Simply push all valid children.
	// Optimization: You could sort these by distance so the closest is popped last.
	for (int i = 0; i < c->node->num_childs; i++)
	{
		if (c->dist.v[i] < c->best_dist)
		{
			c->stack[c->stack_ptr++] = c->node->childs[i];
		}
	}
}

static void	ft_shoot_ray_obj_init(t_bvh_context *c, t_ray ray, float max_dist,
		int root)
{
	c->aabb_c.r_org[0] = (t_v3f){{ray.origin.x, ray.origin.x, ray.origin.x,
		ray.origin.x}};
	c->aabb_c.r_org[1] = (t_v3f){{ray.origin.y, ray.origin.y, ray.origin.y,
		ray.origin.y}};
	c->aabb_c.r_org[2] = (t_v3f){{ray.origin.z, ray.origin.z, ray.origin.z,
		ray.origin.z}};
	c->aabb_c.r_inv[0] = (t_v3f){{ray.inv_dir.x, ray.inv_dir.x, ray.inv_dir.x,
		ray.inv_dir.x}};
	c->aabb_c.r_inv[1] = (t_v3f){{ray.inv_dir.y, ray.inv_dir.y, ray.inv_dir.y,
		ray.inv_dir.y}};
	c->aabb_c.r_inv[2] = (t_v3f){{ray.inv_dir.z, ray.inv_dir.z, ray.inv_dir.z,
		ray.inv_dir.z}};
	c->best_dist = max_dist;
	c->best_index = -1;
	c->stack_ptr = 0;
	c->node_idx = root;
}

void	ft_setup_bounds_4x(t_scene *scene, t_bounds_4x *bounds_4x,
		t_bvh_node *node)
{
	t_bounds	bounds[4];
	int			i;

	i = 0;
	while (i < node->num_childs)
	{
		bounds[i] = scene->bvh_nodes[node->childs[i]].bounds;
		i++;
	}
	*bounds_4x = ft_get_bounds_4x(&bounds[0], &bounds[1], &bounds[2],
			&bounds[3]);
}

float	ft_shoot_ray_against_objects(t_ray ray, float max_dist, t_scene *scene,
		int *hit)
{
	t_bvh_context	c;
	int				explored;

	ft_shoot_ray_obj_init(&c, ray, max_dist, scene->bvh_root);
	explored = 0;
	while (c.node_idx != -1)
	{
		explored++;
		c.node = &scene->bvh_nodes[c.node_idx];
		if (c.node->num_childs == 0)
		{
			ft_check_objects_collisions(ray, c.node->object_index, &c,
				&scene->objects[c.node->object_index]);
		}
		else 
		{
			ft_setup_bounds_4x(scene, &c.aabb_c.bounds_4x, c.node);
			ft_intersect_aabb_x4(c.aabb_c, &c.dist);
			ft_push_next_node_to_stack(&c);
		}
		if (c.stack_ptr > 0)
			c.node_idx = c.stack[--c.stack_ptr];
		else
			c.node_idx = -1;
	}
	if (c.best_dist < max_dist)
		*hit = c.best_index;
	return ((float)explored * 20.0f);
	//return (c.best_dist);
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
