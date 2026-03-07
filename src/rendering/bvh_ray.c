/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:43:04 by pberne            #+#    #+#             */
/*   Updated: 2026/03/07 16:52:20 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// Maybe push closest first
void	ft_push_next_node_to_stack(t_bvh_context *c)
{
	int	i;

	i = 0;
	while (i < c->node->num_childs)
	{
		if (c->dist.v[i] < c->best_dist)
			c->stack[c->stack_ptr++] = (t_bvh_stack_item){c->node->childs[i],
				c->dist.v[i]};
		i++;
	}
}

static inline void	ft_shoot_ray_obj_init(t_bvh_context *c, t_ray ray,
		float max_dist, int root)
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
	c->node_idx.id = root;
	c->node_idx.distance = 1000000.0f;
}

float	ft_shoot_ray_against_objects(t_ray ray, float max_dist, t_scene *scene,
		int *hit)
{
	t_bvh_context	c;

	c = (t_bvh_context){0};
	ft_shoot_ray_obj_init(&c, ray, max_dist, scene->bvh_root);
	while (c.node_idx.id != -1)
	{
		c.node = &scene->bvh_nodes[c.node_idx.id];
		if (c.node->num_childs == 0)
		{
			ft_check_objects_collisions(ray, c.node->object_index, &c,
				&scene->objects[c.node->object_index]);
		}
		else
		{
			ft_intersect_aabb_x4(c.aabb_c, &c.node->bounds_4x, &c.dist);
			ft_push_next_node_to_stack(&c);
		}
		ft_get_next_node(&c);
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
