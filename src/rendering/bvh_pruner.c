/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_pruner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:28:18 by pberne            #+#    #+#             */
/*   Updated: 2026/03/07 15:04:23 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// Traverse the collapsed array and map the optimal indices to avoid gaps
static void	ft_map_active_nodes(t_scene *scene, int node_id, int *map,
		int *current_count)
{
	t_bvh_node	*node;
	int			i;

	if (node_id == -1)
		return ;
	map[node_id] = (*current_count)++;
	node = &scene->bvh_nodes[node_id];
	i = 0;
	while (i < node->num_childs)
	{
		ft_map_active_nodes(scene, node->childs[i], map, current_count);
		i++;
	}
}

// Fills the prune dnode array with the remaped locations
void	ft_move_nodes_to_new_location(t_prune_context *c, t_scene *scene)
{
	c->i = 0;
	while (c->i < scene->bvh_node_capacity)
	{
		if (c->map[c->i] != -1)
		{
			c->new_pos = c->map[c->i];
			scene->bvh_nodes_pruned[c->new_pos] = scene->bvh_nodes[c->i];
			c->j = 0;
			while (c->j < 4)
			{
				c->old_child = scene->bvh_nodes_pruned[c->new_pos].childs[c->j];
				if (c->old_child != -1)
					scene->bvh_nodes_pruned[c->new_pos].childs[c->j]
						= c->map[c->old_child];
				c->j++;
			}
		}
		c->i++;
	}
}

// Removes empty nodes created by the collapse
int	ft_prune_bvh(t_scene *scene, int root_id)
{
	t_prune_context	c;

	c.map = ft_malloc(sizeof(int) * scene->bvh_node_capacity);
	ft_memset_int(c.map, -1, scene->bvh_node_capacity);
	c.active_count = 0;
	ft_map_active_nodes(scene, root_id, c.map, &c.active_count);
	ft_move_nodes_to_new_location(&c, scene);
	c.tmp = scene->bvh_nodes;
	scene->bvh_nodes = scene->bvh_nodes_pruned;
	scene->bvh_nodes_pruned = c.tmp;
	scene->bvh_node_count = c.active_count;
	c.new_root = c.map[root_id];
	ft_free(c.map);
	return (c.new_root);
}
