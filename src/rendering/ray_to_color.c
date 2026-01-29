/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:57:51 by pberne            #+#    #+#             */
/*   Updated: 2026/01/29 22:19:50 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
	this is where the ray bounces and split are processed
	handle reflection / transparency here
	Because the planes cannot really fit into a box, they are excluded
	from the bvh, so we check them first and use a negative hit index
	offset by one to avoid zero to represent them
*/
t_v3d	ft_get_pixel_color(t_ray ray, t_scene *scene)
{
	t_pixel_color_context	c;
	t_material mat;

	c.out_color = (t_v3d){{0, 0, 0}};
	c.distance = ft_shoot_ray(ray, scene, &c.hit);
	if (c.distance < INFINITY)
	{
		c.hit_point = ft_ray_at(ray, c.distance - EPSILON);
		c.hit_normal = ft_get_hit_normal(c.hit_point, scene, c.hit);

		if (c.hit < 0)
			mat = scene->planes[-c.hit - 1].material;
		else
			mat = scene->objects[c.hit].material;
		c.out_color = mat.color;
		c.light_color = ft_get_light(c.hit_point, c.hit_normal, scene);
		c.out_color = ft_v3d_mult(c.out_color, c.light_color);
		if (mat.reflection > 0.0 && ray.remaining_bounces > 0)
		{
			ray.origin = c.hit_point;
			ray = ft_setup_ray_direction(ray, ft_v3d_reflect(ray.direction, c.hit_normal), ray.remaining_bounces - 1);
			return (ft_v3d_lerp(c.out_color, ft_get_pixel_color(ray, scene), mat.reflection));
		}
		else
			return (c.out_color);
	}
	return ((t_v3d){{0.05, 0.05, 0.05}});
}
 