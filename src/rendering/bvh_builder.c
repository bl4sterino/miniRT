/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:16:18 by pberne            #+#    #+#             */
/*   Updated: 2026/03/30 16:53:42 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_find_best_surface_on_axis_split(t_object *objs, int object_count,
		int axis, t_bvh_best_context *best)
{
	int			i;
	t_bounds	left;
	t_bounds	right;
	double		surface;

	ft_quicksort_objects(objs, 0, object_count - 1, axis);
	i = 1;
	while (i < object_count)
	{
		left = ft_get_bounds_range(objs, 0, i);
		right = ft_get_bounds_range(objs, i, object_count - i);
		surface = (ft_get_bounds_surface(left) * i)
			+ (ft_get_bounds_surface(right) * (object_count - i));
		if (surface < best->surface)
		{
			best->surface = surface;
			best->left_id = i;
			best->axis = axis;
		}
		i += best->iterator;
	}
}

int	ft_find_best_split(t_object *objs, int object_count, t_bounds parent_bounds,
		int *left_elements)
{
	t_bvh_best_context	best;

	best.axis = -1;
	best.surface = FT_INFINITY;
	if (object_count < 2)
		return (-1);
	else if (object_count == 2)
	{
		best.axis = ft_get_longest_bounds_axis(parent_bounds);
		ft_quicksort_objects(objs, 0, object_count - 1, best.axis);
		*left_elements = 1;
		return (best.axis);
	}
	if (object_count > 16)
		best.iterator = (int)sqrtf((float)object_count);
	else
		best.iterator = 1;
	ft_find_best_surface_on_axis_split(objs, object_count, 0, &best);
	ft_find_best_surface_on_axis_split(objs, object_count, 1, &best);
	ft_find_best_surface_on_axis_split(objs, object_count, 2, &best);
	if (best.axis != 2)
		ft_quicksort_objects(objs, 0, object_count - 1, best.axis);
	*left_elements = best.left_id;
	return (best.axis);
}

t_bounds	ft_get_bounds_range(t_object *objects, int start,
		int branch_elements)
{
	t_bounds	bounds;
	t_bounds	bounds_check;
	int			i;

	i = start + 1;
	bounds = objects[start].bounds;
	while (i < start + branch_elements)
	{
		bounds_check = objects[i].bounds;
		bounds.min.x = fmin(bounds.min.x, bounds_check.min.x);
		bounds.min.y = fmin(bounds.min.y, bounds_check.min.y);
		bounds.min.z = fmin(bounds.min.z, bounds_check.min.z);
		bounds.max.x = fmax(bounds.max.x, bounds_check.max.x);
		bounds.max.y = fmax(bounds.max.y, bounds_check.max.y);
		bounds.max.z = fmax(bounds.max.z, bounds_check.max.z);
		i++;
	}
	return (bounds);
}

/* Split and sort by splitting plane, or assign the elements to the leaf */
int	ft_bvh_builder(t_scene *scene, int start, int branch_elements)
{
	int			node_id;
	int			left_elements;
	t_bvh_node	*node;

	node_id = ft_bvh_new_node(scene);
	node = &scene->bvh_nodes[node_id];
	node->bounds = ft_get_bounds_range(scene->objects, start, branch_elements);
	if (branch_elements > BVH_MAX_OBJ_PER_LEAF)
	{
		node->split_axis = ft_find_best_split(&scene->objects[start],
				branch_elements, node->bounds, &left_elements);
		node->left = ft_bvh_builder(scene, start, left_elements);
		node->right = ft_bvh_builder(scene, start + left_elements,
				branch_elements - left_elements);
	}
	else
	{
		node->num_obj = branch_elements;
		node->start = start;
		node->left = -1;
		node->right = -1;
	}
	return (node_id);
}
