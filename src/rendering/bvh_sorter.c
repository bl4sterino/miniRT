/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_sorter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:51:58 by pberne            #+#    #+#             */
/*   Updated: 2026/04/10 19:16:04 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float	ft_get_axis_center(t_object *obj, int axis)
{
	float	min_val;
	float	max_val;

	min_val = obj->bounds.min.v[axis];
	max_val = obj->bounds.max.v[axis];
	return ((min_val + max_val) * 0.5f);
}

void	ft_swap_objects(t_object *a, t_object *b)
{
	t_object	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	ft_partition(t_object *objs, int low, int high, int axis)
{
	float	pivot_val;
	int		i;
	int		j;

	pivot_val = ft_get_axis_center(&objs[high], axis);
	i = (low - 1);
	j = low;
	while (j < high)
	{
		if (ft_get_axis_center(&objs[j], axis) < pivot_val)
		{
			i++;
			if (i != j)
				ft_swap_objects(&objs[i], &objs[j]);
			;
		}
		j++;
	}
	if (i + 1 != high)
		ft_swap_objects(&objs[i + 1], &objs[high]);
	return (i + 1);
}

void	ft_quicksort_objects(t_object *objs, int low, int high, int axis)
{
	int	partition_index;

	if (low < high)
	{
		partition_index = ft_partition(objs, low, high, axis);
		ft_quicksort_objects(objs, low, partition_index - 1, axis);
		ft_quicksort_objects(objs, partition_index + 1, high, axis);
	}
}
