/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 20:03:40 by pberne            #+#    #+#             */
/*   Updated: 2026/01/25 21:08:18 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	ft_bounds_collision(t_ray ray, t_bounds b)
{
	double	t1;
	double	t2;
	double	tmin;
	double	tmax;

	t1 = (b.min.x - ray.origin.x) * ray.inv_dir.x;
	t2 = (b.max.x - ray.origin.x) * ray.inv_dir.x;
	tmin = fmin(t1, t2);
	tmax = fmax(t1, t2);
	t1 = (b.min.y - ray.origin.y) * ray.inv_dir.y;
	t2 = (b.max.y - ray.origin.y) * ray.inv_dir.y;
	tmin = fmax(tmin, fmin(t1, t2));
	tmax = fmin(tmax, fmax(t1, t2));
	t1 = (b.min.z - ray.origin.z) * ray.inv_dir.z;
	t2 = (b.max.z - ray.origin.z) * ray.inv_dir.z;
	tmin = fmax(tmin, fmin(t1, t2));
	tmax = fmin(tmax, fmax(t1, t2));
	if (tmax < 0 || tmin > tmax)
		return (-1.0);
	if (tmin < 0)
		return (0.0);
	return (tmin);
}
