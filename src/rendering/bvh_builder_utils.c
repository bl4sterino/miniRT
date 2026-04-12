/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:16:18 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 10:01:40 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_build_bounds_2x(t_bvh_node *node, t_bvh_node *left,
		t_bvh_node *right)
{
	node->bounds2x.min_x = v3f(fminf(left->bounds2x.min_x.v[0],
				left->bounds2x.min_x.v[1]), fminf(right->bounds2x.min_x.v[0],
				right->bounds2x.min_x.v[1]), 0.0f);
	node->bounds2x.max_x = v3f(fmaxf(left->bounds2x.max_x.v[0],
				left->bounds2x.max_x.v[1]), fmaxf(right->bounds2x.max_x.v[0],
				right->bounds2x.max_x.v[1]), 0.0f);
	node->bounds2x.min_y = v3f(fminf(left->bounds2x.min_y.v[0],
				left->bounds2x.min_y.v[1]), fminf(right->bounds2x.min_y.v[0],
				right->bounds2x.min_y.v[1]), 0.0f);
	node->bounds2x.max_y = v3f(fmaxf(left->bounds2x.max_y.v[0],
				left->bounds2x.max_y.v[1]), fmaxf(right->bounds2x.max_y.v[0],
				right->bounds2x.max_y.v[1]), 0.0f);
	node->bounds2x.min_z = v3f(fminf(left->bounds2x.min_z.v[0],
				left->bounds2x.min_z.v[1]), fminf(right->bounds2x.min_z.v[0],
				right->bounds2x.min_z.v[1]), 0.0f);
	node->bounds2x.max_z = v3f(fmaxf(left->bounds2x.max_z.v[0],
				left->bounds2x.max_z.v[1]), fmaxf(right->bounds2x.max_z.v[0],
				right->bounds2x.max_z.v[1]), 0.0f);
}

void	ft_bvh_bounds_2x(t_scene *scene, t_bvh_node *node)
{
	t_bvh_node	*left;
	t_bvh_node	*right;

	left = &scene->bvh_nodes[node->left];
	right = &scene->bvh_nodes[node->right];
	if (node->left != -1)
	{
		ft_bvh_bounds_2x(scene, &scene->bvh_nodes[node->left]);
		ft_bvh_bounds_2x(scene, &scene->bvh_nodes[node->right]);
	}
	else
	{
		node->bounds2x.min_x = v3f_a(node->bounds.min.x);
		node->bounds2x.max_x = v3f_a(node->bounds.max.x);
		node->bounds2x.min_y = v3f_a(node->bounds.min.y);
		node->bounds2x.max_y = v3f_a(node->bounds.max.y);
		node->bounds2x.min_z = v3f_a(node->bounds.min.z);
		node->bounds2x.max_z = v3f_a(node->bounds.max.z);
		return ;
	}
	ft_build_bounds_2x(node, left, right);
}

int	ft_update_bvh(t_scene *scene, int start, int branch_elements)
{
	int	rootid;

	scene->bvh_node_count = 0;
	ft_memcpy(scene->objects, scene->raw_objects, sizeof(t_object)
		* scene->num_objects);
	rootid = ft_bvh_builder(scene, start, branch_elements);
	if (rootid >= 0)
		ft_bvh_bounds_2x(scene, &scene->bvh_nodes[rootid]);
	return (rootid);
}
