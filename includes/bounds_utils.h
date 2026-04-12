/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:21:48 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 10:27:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOUNDS_UTILS_H
# define BOUNDS_UTILS_H

# include "rt.h"

static inline t_bounds	ft_empty_bounds(void)
{
	t_bounds	b;

	b.min = v3f(FT_INFINITY, FT_INFINITY, FT_INFINITY);
	b.max = v3f(-FT_INFINITY, -FT_INFINITY, -FT_INFINITY);
	return (b);
}

static inline t_bounds	ft_combine_bounds(t_bounds a, t_bounds b)
{
	t_bounds	res;

	res.min = ft_v3f_min(a.min, b.min);
	res.max = ft_v3f_max(a.max, b.max);
	return (res);
}

static inline t_bounds	ft_processed_bounds(t_bounds b)
{
	b.center.v = (b.min.v + b.max.v) * 0.5f;
	return (b);
}

#endif