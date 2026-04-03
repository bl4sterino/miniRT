/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray_smart.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 17:27:45 by pberne            #+#    #+#             */
/*   Updated: 2026/04/03 13:50:17 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	ft_shoot_ray_smart(t_ray ray, t_scene *scene, t_pixel_color_context *c,
		int ray_target)
{
	if (ray_target == SELECTED_NONE)
		return (ft_shoot_ray(ray, scene, &c->hit));
	else if (ray_target == SELECTED_SKYBOX)
		return (FT_INFINITY);
	else
		return (ft_get_object_distance(ray, scene, ray_target, &c->hit));
}
