/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:57:51 by pberne            #+#    #+#             */
/*   Updated: 2026/01/29 18:25:01 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
	this is where the ray bounces and split are processed
	handle reflection / transparency here
	Because the planes cannot really fit into a box, they are excluded
	from the bvh, so we check them first and use a negative hit index to
	represent them
*/
t_v3d	ft_get_pixel_color(t_ray ray, t_scene *scene)
{
	t_pixel_color_context	c;

	c.out_color = (t_v3d){{0, 0, 0}};
	c.distance = ft_shoot_ray(ray, scene, &c.hit);
	if (c.distance < INFINITY)
	{
		c.hit_point = ft_ray_at(ray, c.distance - EPSILON);
		c.hit_normal = ft_get_hit_normal(c.hit_point, scene, c.hit);
		if (c.hit < 0)
			c.out_color = scene->planes[-c.hit - 1].material.color;
		else
			c.out_color = scene->objects[c.hit].material.color;
		c.color = ft_get_light(c.hit_point, c.hit_normal, scene);
		return (ft_v3d_mult(c.out_color, c.color));
	}
	return ((t_v3d){{0.05, 0.05, 0.05}});
}
