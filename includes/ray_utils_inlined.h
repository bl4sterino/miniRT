/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils_inlined.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:33:34 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 13:50:28 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_UTILS_INLINED_H
# define RAY_UTILS_INLINED_H

# include "rt.h"

static inline t_v3d	ft_ray_at(t_ray ray, double d)
{
	return (ft_v3d_add(ray.origin, ft_v3d_scale(ray.direction, d)));
}

#endif