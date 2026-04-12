/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 09:56:33 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 11:08:33 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_UTILS_H
# define BVH_UTILS_H

# include "rt.h"

static inline void	ft_swap_objects(t_object *a, t_object *b)
{
	t_object	temp;

	if (a != b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

static inline int	ft_bvh_new_node(t_scene *scene)
{
	int	id;

	id = scene->bvh_node_count++;
	ft_bzero(&scene->bvh_nodes[id], sizeof(t_bvh_node));
	scene->bvh_nodes[id].bounds = ft_empty_bounds();
	return (id);
}

static inline int	ft_get_longest_bounds_axis(t_bounds bounds)
{
	t_v3d	length;
	int		axis;

	length.x = bounds.max.x - bounds.min.x;
	length.y = bounds.max.y - bounds.min.y;
	length.z = bounds.max.z - bounds.min.z;
	if (length.x > length.y && length.x > length.z)
		axis = 0;
	else if (length.y > length.z)
		axis = 1;
	else
		axis = 2;
	return (axis);
}

static inline float	ft_get_bounds_surface(t_bounds bounds)
{
	t_v3f	size;

	size.v = bounds.max.v - bounds.min.v;
	return (2.0f * (size.x * size.y + size.x * size.z + size.y * size.z));
}

#endif