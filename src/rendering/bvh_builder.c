/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:16:18 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 11:09:38 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "rt.h"

// Computes a Split on a specific axis by pushing items into N bins and
// comparing their SAH
void	ft_find_best_split_binned(t_object *objs, t_v2i count_axis,
		t_bounds parent, t_bvh_best_context *best)
{
	t_find_best_split_context	c;

	c.min_p = parent.min.v[count_axis.y];
	c.max_p = parent.max.v[count_axis.y];
	c.range = c.max_p - c.min_p;
	if (c.range < EPSILON)
		return ;
	ft_fill_bins(&c, objs, count_axis.y, count_axis.x);
	ft_get_right_merged_bins(&c);
	ft_compare_merged_bins(&c, best, count_axis.y);
}

// In case there was a tie for the split axis, we default to longest axis,
// If there is a tie in longest axis, we just split the object
void	ft_split_fallbacks(t_split_bvh_context *c, t_scene *scene, int start,
		int branch_elements)
{
	if (c->best.axis != -1)
		c->left_count = ft_partition_by_val(&scene->objects[start],
				branch_elements, c->best.axis, c->best.split_val);
	if (c->left_count <= 0 || c->left_count >= branch_elements)
	{
		c->best.axis = ft_get_longest_bounds_axis(c->node->bounds);
		c->mid = (c->node->bounds.min.v[c->best.axis]
				+ c->node->bounds.max.v[c->best.axis]) * 0.5f;
		c->left_count = ft_partition_by_val(&scene->objects[start],
				branch_elements, c->best.axis, c->mid);
		if (c->left_count <= 0 || c->left_count >= branch_elements)
			c->left_count = branch_elements / 2;
	}
}

void	ft_split_bvh(t_scene *scene, t_bvh_node *node, int start,
		int branch_elements)
{
	t_split_bvh_context	c;

	c.best.surface = FT_INFINITY;
	c.best.axis = -1;
	c.i = -1;
	c.node = node;
	while (++c.i < 3)
		ft_find_best_split_binned(&scene->objects[start],
			(t_v2i){branch_elements, c.i}, node->bounds, &c.best);
	c.left_count = 0;
	ft_split_fallbacks(&c, scene, start, branch_elements);
	node->split_axis = c.best.axis;
	node->left = ft_bvh_builder(scene, start, c.left_count);
	node->right = ft_bvh_builder(scene, start + c.left_count, branch_elements
			- c.left_count);
	node->num_obj = 0;
}

int	ft_bvh_builder(t_scene *scene, int start, int branch_elements)
{
	int			node_id;
	t_bvh_node	*node;
	int			i;

	i = -1;
	if (branch_elements <= 0)
		return (-1);
	node_id = ft_bvh_new_node(scene);
	node = &scene->bvh_nodes[node_id];
	while (++i < branch_elements)
		node->bounds = ft_combine_bounds(node->bounds, scene->objects[start
				+ i].bounds);
	if (branch_elements > 1)
		ft_split_bvh(scene, node, start, branch_elements);
	else
	{
		node->num_obj = 1;
		node->start = start;
		node->left = -1;
		node->right = -1;
	}
	return (node_id);
}
