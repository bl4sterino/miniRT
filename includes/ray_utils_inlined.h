/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils_inlined.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:33:34 by pberne            #+#    #+#             */
/*   Updated: 2026/02/26 15:13:18 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_UTILS_INLINED_H
# define RAY_UTILS_INLINED_H

# include "rt.h"

static inline t_v3f	ft_ray_at(t_ray ray, float d)
{
	return (ft_v3f_add(ray.origin, ft_v3f_scale(ray.direction, d)));
}

static inline t_ray	ft_setup_ray_target(t_ray ray, t_v3f target, char bounces)
{
	ray.direction = ft_v3f_normalize(ft_v3f_sub(target, ray.origin));
	ray.inv_dir = ft_v3f_div_safe((t_v3f){{1, 1, 1}}, ray.direction);
	ray.inv_sign[0] = ray.inv_dir.x < 0.0f;
	ray.inv_sign[1] = ray.inv_dir.y < 0.0f;
	ray.inv_sign[2] = ray.inv_dir.z < 0.0f;
	ray.remaining_bounces = bounces;
	return (ray);
}

static inline t_ray	ft_setup_ray_direction(t_ray ray, t_v3f dir, char bounces)
{
	ray.direction = ft_v3f_normalize(dir);
	ray.inv_dir = ft_v3f_div_safe((t_v3f){{1.0f, 1.0f, 1.0f}}, ray.direction);
	ray.inv_sign[0] = ray.inv_dir.x < 0.0f;
	ray.inv_sign[1] = ray.inv_dir.y < 0.0f;
	ray.inv_sign[2] = ray.inv_dir.z < 0.0f;
	ray.remaining_bounces = bounces;
	return (ray);
}

#endif