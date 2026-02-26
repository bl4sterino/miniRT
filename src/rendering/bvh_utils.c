/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 18:50:48 by pberne            #+#    #+#             */
/*   Updated: 2026/02/26 15:05:35 by pberne           ###   ########.fr       */
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

float	ft_get_bounds_surface(t_bounds bounds)
{
	t_v3f	side_length;
	t_v3f	axis_area;
	int		i;

	i = 0;
	while (i < 3)
	{
		side_length.v[i] = bounds.max.v[i] - bounds.min.v[i];
		i++;
	}
	axis_area.x = side_length.y * side_length.z;
	axis_area.y = side_length.x * side_length.z;
	axis_area.z = side_length.x * side_length.y;
	return ((axis_area.x + axis_area.y + axis_area.z) * 2.0f);
}
