/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:50:48 by pberne            #+#    #+#             */
/*   Updated: 2026/01/26 13:10:57 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_get_longest_bounds_axis(t_bounds bounds)
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
