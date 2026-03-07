/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:16:18 by pberne            #+#    #+#             */
/*   Updated: 2026/03/06 19:47:09 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*void	ft_find_best_surface_on_axis_split(t_object *objs, int object_count,
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
		i++;
	}
}*/


void	ft_find_best_surface_on_axis_split(t_object *objs,
		int axis, t_bvh_best_context *best, int object_in_split[4])
{
	int i = 0;
	int offset = 0;
	float surface = 0.0f;
	float total_surface = 0.0f;
	t_bounds split_bounds;
	
	while (i < 4)
	{
		split_bounds = ft_get_bounds_range(objs, offset, object_in_split[i]);
		surface = ft_get_bounds_surface(split_bounds);
		total_surface += surface * (float)object_in_split[i];
		i++;
	}
	if (total_surface < best->surface)
	{
		best->axis = axis;
		best->surface = total_surface;
	}
}

void ft_set_object_in_split(int object_count, int object_in_split[4])
{
	int increment = object_count / 4;
	
	object_in_split[0] = object_count - increment * 3;
	object_in_split[1] = increment;
	object_in_split[2] = increment;
	object_in_split[3] = increment;
}

int	ft_find_best_split(t_object *objs, int object_count,
		int object_in_split[4])
{
	t_bvh_best_context	best;

	best.axis = -1;
	best.surface = INFINITY;

	ft_quicksort_objects(objs, 0, object_count - 1, AXIS_X);
	ft_find_best_surface_on_axis_split(objs, 0, &best, object_in_split);

	ft_quicksort_objects(objs, 0, object_count - 1, AXIS_Y);
	ft_find_best_surface_on_axis_split(objs, 1, &best, object_in_split);

	ft_quicksort_objects(objs, 0, object_count - 1, AXIS_Z);
	ft_find_best_surface_on_axis_split(objs, 2, &best, object_in_split);
	
	if (best.axis != AXIS_Z)
		ft_quicksort_objects(objs, 0, object_count - 1, best.axis);
	
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
		bounds.min = ft_v3f_min(bounds.min, bounds_check.min);
		bounds.max = ft_v3f_max(bounds.max, bounds_check.max);
		i++;
	}
	return (bounds);
}

void	ft_split_for_leaf(int branch_elements, int element_count[4])
{
	int	i;

	i = 0;
	while (i < branch_elements)
	{
		element_count[i] = 1;
		i++;
	}
}

/* Split and sort by splitting plane, or assign the elements to the leaf */
int	ft_bvh_builder(t_scene *scene, int start, int branch_elements)
{
	int			node_id;
	int			elements_count[4];
	t_bvh_node	*node;
	int			i;
	int			child_start_offset;

	i = -1;
	node_id = ft_bvh_new_node(scene);
	node = &scene->bvh_nodes[node_id];
	node->object_index = start;
	node->bounds = ft_get_bounds_range(scene->objects, start, branch_elements);
	if(branch_elements == 1)
	{
		node->num_childs = 0;
		ft_printf("Node %d: start %d, childs %d\n", node_id, start, node->num_childs);
		ft_printf("min x: %f, y: %f, z: %f\n", node->bounds.min.x,node->bounds.min.y, node->bounds.min.z);
		ft_printf("max x: %f, y: %f, z: %f\n\n", node->bounds.max.x,node->bounds.max.y, node->bounds.max.z);
		return(node_id);
	}
	node->num_childs = ft_min(branch_elements, 4);
	ft_set_object_in_split(branch_elements, elements_count);
	if (branch_elements > 4)
		ft_find_best_split(&scene->objects[start], branch_elements, elements_count);
	else
		ft_split_for_leaf(branch_elements, elements_count);
	child_start_offset = start;
	while (++i < node->num_childs)
	{
		node->childs[i] = ft_bvh_builder(scene, child_start_offset, elements_count[i]);
		child_start_offset += elements_count[i];

	}
	while (i < 4)
	{
		node->childs[i] = -1;
		i++;
	}
	ft_printf("Node %d: start %d, childs %d\n", node_id, start, node->num_childs);
	ft_printf("min x: %f, y: %f, z: %f\n", node->bounds.min.x,node->bounds.min.y, node->bounds.min.z);
	ft_printf("max x: %f, y: %f, z: %f\n\n", node->bounds.max.x,node->bounds.max.y, node->bounds.max.z);
	return (node_id);
}
