/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_ray_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:41:45 by pberne            #+#    #+#             */
/*   Updated: 2026/02/25 14:19:10 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_v3f	ft_get_light(t_v3d position, t_v3d normal, t_scene *scene)
{
	t_get_light_context	c;

	c.i = -1;
	c.color = scene->ambient_light.color;
	while (++c.i < scene->num_lights)
	{
		c.light_ray.origin = position;
		c.light_ray = ft_setup_ray_target(c.light_ray,
				scene->lights[c.i].position, 0);
		c.light_dist = ft_v3d_length(ft_v3d_sub(scene->lights[c.i].position,
					c.light_ray.origin));
		if (ft_v3d_dot(normal, c.light_ray.direction) < 0)
			continue;
		c.plane_dist = ft_shoot_ray_against_planes(c.light_ray, c.light_dist,
				scene, &c.hit);
		if (c.plane_dist < c.light_dist)
			continue ;
		c.dist = ft_shoot_ray_against_objects(c.light_ray, c.light_dist, scene,
				&c.hit);
		if (c.dist >= c.light_dist - EPSILON)
		{
			c.new_color = ft_v3f_scale(scene->lights[c.i].color,
					fabs(ft_v3d_dot(c.light_ray.direction, normal)));
			c.color = ft_v3f_add(c.color, c.new_color);
		}
	}
	return (c.color);
}
