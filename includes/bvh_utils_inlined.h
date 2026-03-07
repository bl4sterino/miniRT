/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils_inlined.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 16:27:18 by pberne            #+#    #+#             */
/*   Updated: 2026/03/07 16:27:56 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_UTILS_INLINED_H
# define BVH_UTILS_INLINED_H

# include "rt.h"

static inline void	ft_get_next_node(t_bvh_context *c)
{
	c->node_idx.id = -1;
	while (c->stack_ptr > 0)
	{
		c->next = c->stack[--c->stack_ptr];
		if (c->next.distance < c->best_dist)
		{
			c->node_idx.id = c->next.id;
			break ;
		}
	}
}

#endif