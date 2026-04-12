/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_builder_split_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:13:08 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 11:10:53 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// Traverse the array of object and "assigns" each objects to a bin
void	ft_fill_bins(t_find_best_split_context *c, t_object *objs, int axis,
		int count)
{
	int	i;
	int	bin_index;

	i = 0;
	while (i < BIN_COUNT)
	{
		c->bins[i].count = 0;
		c->bins[i].bounds = ft_empty_bounds();
		i++;
	}
	i = 0;
	while (i < count)
	{
		bin_index = (int)((objs[i].bounds.center.v[axis] - c->min_p) / c->range
				* BIN_COUNT);
		bin_index = ft_clampi(bin_index, 0, BIN_COUNT - 1);
		c->bins[bin_index].count++;
		c->bins[bin_index].bounds = ft_combine_bounds(c->bins[bin_index].bounds,
				objs[i].bounds);
		i++;
	}
}

// Traverse the bins and incrementally computes the size
// and object count of merged bins from right to left
void	ft_get_right_merged_bins(t_find_best_split_context *c)
{
	int	i;

	c->current_bounds = ft_empty_bounds();
	c->current_count = 0;
	i = BIN_COUNT - 1;
	while (i >= 0)
	{
		c->current_bounds = ft_combine_bounds(c->current_bounds,
				c->bins[i].bounds);
		c->current_count += c->bins[i].count;
		c->right_bounds[i] = c->current_bounds;
		c->right_counts[i] = c->current_count;
		i--;
	}
}

// Traverse the bins from left to right and compares the SAH of every bin merge
// to find the best split
void	ft_compare_merged_bins(t_find_best_split_context *c,
		t_bvh_best_context *best, int axis)
{
	int		i;
	float	cost;

	i = -1;
	c->left_bounds = ft_empty_bounds();
	c->left_counts = 0;
	while (++i < BIN_COUNT - 1)
	{
		c->left_bounds = ft_combine_bounds(c->left_bounds, c->bins[i].bounds);
		c->left_counts += c->bins[i].count;
		if (c->left_counts == 0 || c->right_counts[i + 1] == 0)
			continue ;
		cost = (ft_get_bounds_surface(c->left_bounds) * c->left_counts)
			+ (ft_get_bounds_surface(c->right_bounds[i + 1]) * c->right_counts[i
				+ 1]);
		if (cost < best->surface)
		{
			best->surface = cost;
			best->axis = axis;
			best->split_val = c->min_p + (c->range / BIN_COUNT) * (i + 1);
		}
	}
}

// Move the objects to the side they belong to,
int	ft_partition_by_val(t_object *objs, int count, int axis, float split_val)
{
	int			i;
	int			j;

	i = 0;
	j = count - 1;
	while (i <= j)
	{
		if (objs[i].bounds.center.v[axis] < split_val)
			i++;
		else
		{
			ft_swap_objects(&objs[i], &objs[j]);
			j--;
		}
	}
	return (i);
}
