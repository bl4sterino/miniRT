/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:16:18 by pberne            #+#    #+#             */
/*   Updated: 2026/03/07 12:25:07 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_bvh_new_node(t_scene *scene)
{
	int	id;

	id = scene->bvh_node_count++;
	ft_bzero(&scene->bvh_nodes[id], sizeof(t_bvh_node));
	return (id);
}

int	ft_update_bvh(t_scene *scene, int start, int branch_elements)
{
	int	bvh_root;

	scene->bvh_node_count = 0;
	ft_memcpy(scene->objects, scene->raw_objects, sizeof(t_object)
		* scene->num_objects);
	bvh_root = ft_bvh_builder(scene, start, branch_elements);
	bvh_root = ft_collapse_bvh(scene, bvh_root);
	bvh_root = ft_prune_bvh(scene, bvh_root);
	return (bvh_root);
}
