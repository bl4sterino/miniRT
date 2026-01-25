/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:16:18 by pberne            #+#    #+#             */
/*   Updated: 2026/01/25 20:01:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

double	ft_get_axis_pos(int axis, t_bounds bounds)
{
	double	ret;

	if (axis == 0)
		ret = (bounds.min.x + bounds.max.x) * 0.5;
	else if (axis == 1)
		ret = (bounds.min.y + bounds.max.y) * 0.5;
	else
		ret = (bounds.min.z + bounds.max.z) * 0.5;
	return (ret);
}

/* Split and sort by splitting plane, or assign the elements to the leaf */
t_bvh_node	*ft_bvh_builder(t_scene *scene, int start, int branch_elements)
{
	t_bvh_node	*node;
	int			half_elements;

	node = ft_malloc(sizeof(t_bvh_node));
	ft_bzero(node, sizeof(t_bvh_node));
	node->bounds = ft_get_bounds_range(scene->objects, start, branch_elements);
	if (branch_elements > BVH_MAX_OBJ_PER_LEAF)
	{
		ft_sort_range_by_longest_axis(&scene->objects[start], branch_elements,
			node->bounds);
		half_elements = branch_elements * 0.5;
		node->left = ft_bvh_builder(scene, start, half_elements);
		node->right = ft_bvh_builder(scene, start + half_elements,
				branch_elements - half_elements);
	}
	else
	{
		node->num_obj = branch_elements;
		node->start = start;
	}
	return (node);
}
