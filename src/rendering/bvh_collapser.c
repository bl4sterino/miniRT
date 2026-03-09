/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_collapser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 09:36:37 by pberne            #+#    #+#             */
/*   Updated: 2026/03/07 16:52:20 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_push_childs(t_collapse_context *c, t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		c->child = &scene->bvh_nodes[c->binary_children[i]];
		if (c->child->num_childs > 0)
		{
			c->node->childs[c->count] = ft_collapse_bvh(scene,
					c->child->childs[0]);
			c->child_bounds[c->count++]
				= scene->bvh_nodes[c->child->childs[0]].bounds;
			c->node->childs[c->count] = ft_collapse_bvh(scene,
					c->child->childs[1]);
			c->child_bounds[c->count++]
				= scene->bvh_nodes[c->child->childs[1]].bounds;
		}
		else
		{
			c->node->childs[c->count] = ft_collapse_bvh(scene,
					c->binary_children[i]);
			c->child_bounds[c->count++] = c->child->bounds;
		}
	}
}

// Collapse binary bvh into quaternary
int	ft_collapse_bvh(t_scene *scene, int node_id)
{
	t_collapse_context	c;

	if (node_id == -1)
		return (-1);
	c.node = &scene->bvh_nodes[node_id];
	if (c.node->num_childs == 0)
		return (node_id);
	c.binary_children[0] = c.node->childs[0];
	c.binary_children[1] = c.node->childs[1];
	c.count = 0;
	ft_push_childs(&c, scene);
	c.node->num_childs = c.count;
	c.i = c.count - 1;
	while (++c.i < 4)
	{
		c.node->childs[c.i] = -1;
		c.child_bounds[c.i] = (t_bounds){(t_v3f){{FT_INFINITY, FT_INFINITY,
			FT_INFINITY}}, (t_v3f){{-FT_INFINITY, -FT_INFINITY, -FT_INFINITY}}};
	}
	c.node->bounds_4x = ft_get_bounds_4x(&c.child_bounds[0], &c.child_bounds[1],
			&c.child_bounds[2], &c.child_bounds[3]);
	return (node_id);
}
