/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:57:51 by pberne            #+#    #+#             */
/*   Updated: 2026/02/25 16:50:21 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline t_v3f	ft_get_sky_color(t_ray ray)
{
	float	dot;

	dot = (float)ft_v3d_dot(ray.direction, (t_v3d){{0.0, 1.0, 0.0}});
	dot = (dot + 1) * 0.5f;
	dot = 0.05f + 0.1f * dot;
	return ((t_v3f){{dot, dot, dot}});
}

/*
	this is where the ray bounces and split are processed
	handle reflection / transparency here
	Because the planes cannot really fit into a box, they are excluded
	from the bvh, so we check them first and use a negative hit index
	offset by one to avoid zero to represent them
*/
t_v3f	ft_get_pixel_color(t_ray ray, t_scene *scene, t_v3d *hit_normal)
{
	t_pixel_color_context	c;

	c.out_color = (t_v3f){{0, 0, 0}};
	c.distance = ft_shoot_ray(ray, scene, &c.hit);
	if (c.distance < INFINITY)
	{
		
		if (c.hit < 0)
			c.mat = scene->planes[-c.hit - 1].material;
		else
			c.mat = scene->objects[c.hit].material;

		c.hit_point = ft_ray_at(ray, c.distance - EPSILON);
		c.hit_normal = ft_get_hit_normal(c.hit_point, scene, c.hit, ray.direction);
		if(hit_normal)
			*hit_normal = c.hit_normal;

		if (c.mat.emission > 0.0)
			return (ft_v3f_scale(c.mat.color, c.mat.emission));

	

		c.out_color = c.mat.color;
		if (ray.remaining_bounces > 0)
		{
			ray.origin = c.hit_point;
			double do_reflect = fast_rand();
			if(do_reflect < c.mat.reflectiveness)
			{
				c.reflected = ft_v3d_reflect(ray.direction, c.hit_normal);
				c.new_dir = ft_v3d_normalize(ft_v3d_lerp(c.reflected, ft_v3d_random_hemisphere(c.hit_normal), c.mat.diffusion));
				ray = ft_setup_ray_direction(ray, c.new_dir, ray.remaining_bounces - 1);
				return (ft_get_pixel_color(ray, scene, hit_normal));
			}
			else
			{
				ray = ft_setup_ray_direction(ray, ft_v3d_random_hemisphere(c.hit_normal), ray.remaining_bounces - 1);
				c.light_color = ft_v3f_add(ft_get_light(c.hit_point, c.hit_normal, scene), ft_get_pixel_color(ray, scene, 0));
				return (ft_v3f_mult(c.out_color, c.light_color));
			}
		}
		else
			c.out_color = ft_v3f_mult(c.out_color, ft_get_light(c.hit_point, c.hit_normal, scene));
		return (c.out_color);
	}
	if(hit_normal)
		*hit_normal = ray.direction;
	return (ft_get_sky_color(ray));
}

