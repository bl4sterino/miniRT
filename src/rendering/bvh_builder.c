/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:16:18 by pberne            #+#    #+#             */
/*   Updated: 2026/01/24 18:30:43 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void ft_build_bvh(t_scene *scene)
{
	t_bvh_node *node;

	node = ft_malloc(sizeof(t_bvh_node));
	ft_bzero(node, sizeof(t_bvh_node));

	node->num_obj = 1;
	t_bounds bounds;
	bounds.min = (t_v3d){-1, -1, -1};
	bounds.max = (t_v3d){20, 1, 20};
	node->bounds = bounds;
	scene->bvh_root = node;
}
