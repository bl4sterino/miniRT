/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_sorter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:51:58 by pberne            #+#    #+#             */
/*   Updated: 2026/01/26 11:04:59 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	ft_get_axis_center(t_object *obj, int axis)
{
	double	min_val;
	double	max_val;

	if (axis == 0)
	{
		min_val = obj->bounds.min.x;
		max_val = obj->bounds.max.x;
	}
	else if (axis == 1)
	{
		min_val = obj->bounds.min.y;
		max_val = obj->bounds.max.y;
	}
	else
	{
		min_val = obj->bounds.min.z;
		max_val = obj->bounds.max.z;
	}
	return ((min_val + max_val) * 0.5);
}

static void	ft_swap_objects(t_object *a, t_object *b)
{
	t_object	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int	ft_partition(t_object *objs, int low, int high, int axis)
{
	double	pivot_val;
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
			ft_swap_objects(&objs[i], &objs[j]);
		}
		j++;
	}
	ft_swap_objects(&objs[i + 1], &objs[high]);
	return (i + 1);
}

static void	ft_quicksort_objects(t_object *objs, int low, int high, int axis)
{
	int	partition_index;

	if (low < high)
	{
		partition_index = ft_partition(objs, low, high, axis);
		ft_quicksort_objects(objs, low, partition_index - 1, axis);
		ft_quicksort_objects(objs, partition_index + 1, high, axis);
	}
}

int	ft_sort_range_by_longest_axis(t_object *objs, int object_count,
		t_bounds range_bounds)
{
	int	axis;

	if (object_count < 2)
		return -1;
	axis = ft_get_longest_bounds_axis(range_bounds);
	ft_quicksort_objects(objs, 0, object_count - 1, axis);
	return (axis);
}
