/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:43:04 by pberne            #+#    #+#             */
/*   Updated: 2026/03/03 15:24:53 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


static inline void	ft_check_objects_collisions(t_ray ray, int object_index,
		t_bvh_context *context, t_object *obj)
{
	float		dist;

	dist = INFINITY;
	if (obj->type == object_type_quad)
		dist = ft_quad_collision(ray, obj->object.as_quad);
	else if (obj->type == object_type_sphere)
		dist = ft_sphere_collision(ray, obj->object.as_sphere);
	else if (obj->type == object_type_cylinder)
		dist = ft_cylinder_collision(ray, obj->object.as_cylinder);
	else if (obj->type == object_type_triangle)
		dist = ft_triangle_collision(ray, obj->object.as_triangle);
	if (dist < context->best_dist)
	{
		context->best_dist = dist;
		context->best_index = object_index;
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

/*float	ft_shoot_ray_against_objects(t_ray ray, float max_dist, t_scene *scene,
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

/* wtf .. */
float ft_shoot_ray_against_objects(t_ray ray, float max_dist, t_scene *scene, int *hit)
{
    t_bvh_context c;
    __m128 r_org[3], r_inv[3];

    // Splat Ray for SIMD
    r_org[0] = _mm_set1_ps(ray.origin.x); r_org[1] = _mm_set1_ps(ray.origin.y); r_org[2] = _mm_set1_ps(ray.origin.z);
    r_inv[0] = _mm_set1_ps(ray.inv_dir.x); r_inv[1] = _mm_set1_ps(ray.inv_dir.y); r_inv[2] = _mm_set1_ps(ray.inv_dir.z);

    c.best_dist = max_dist;
    c.best_index = -1;
    c.stack_ptr = 0;
    
    int node_idx = scene->bvh_root;

    while (1) {
        t_bvh_node *node = &scene->bvh_nodes[node_idx];

        // Leaf Check: If left is -1, it's a leaf
        if (node->left == -1) {
            ft_check_objects_collisions(ray, node->start, &c, &scene->objects[node->start]);
            if (c.stack_ptr == 0) break;
            node_idx = c.stack[--c.stack_ptr];
            continue;
        }

        // Parent node logic
        int l_idx = node->left;
        int r_idx = node->right;

        float d1, d2;
        ft_intersect_aabb_x2_fast(r_org, r_inv, 
                                  &scene->bvh_nodes[l_idx].bounds, 
                                  &scene->bvh_nodes[r_idx].bounds, 
                                  &d1, &d2);

        // Sorting logic to shrink best_dist as fast as possible
        if (d1 < c.best_dist && d2 < c.best_dist) {
            if (d1 < d2) {
                c.stack[c.stack_ptr++] = r_idx;
                node_idx = l_idx;
            } else {
                c.stack[c.stack_ptr++] = l_idx;
                node_idx = r_idx;
            }
        } else if (d1 < c.best_dist) {
            node_idx = l_idx;
        } else if (d2 < c.best_dist) {
            node_idx = r_idx;
        } else {
            if (c.stack_ptr == 0) break;
            node_idx = c.stack[--c.stack_ptr];
        }
    }

    if (c.best_dist < max_dist) *hit = c.best_index;
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
