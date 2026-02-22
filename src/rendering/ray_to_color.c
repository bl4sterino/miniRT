/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:57:51 by pberne            #+#    #+#             */
/*   Updated: 2026/02/22 16:43:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline t_v3d	ft_get_sky_color(t_ray ray)
{
	double	dot;

	dot = ft_v3d_dot(ray.direction, (t_v3d){{0.0, 1.0, 0.0}});
	dot = (dot + 1) * 0.5;
	dot = 0.05 + 0.1 * dot;
	return ((t_v3d){{dot, dot, dot}});
}

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
	t_material				mat;
	char hit_emissive = 0;

	c.out_color = (t_v3d){{0, 0, 0}};
	c.distance = ft_shoot_ray(ray, scene, &c.hit);
	if (c.distance < INFINITY)
	{
		
		if (c.hit < 0)
			mat = scene->planes[-c.hit - 1].material;
		else
			mat = scene->objects[c.hit].material;

		if (mat.emission > 0.0)
			return (ft_v3d_scale(mat.color, mat.emission));

		c.hit_point = ft_ray_at(ray, c.distance - EPSILON);
		c.hit_normal = ft_get_hit_normal(c.hit_point, scene, c.hit, ray.direction);

		c.out_color = mat.color;
		if (ray.remaining_bounces > 0)
		{
			ray.origin = c.hit_point;
			double do_reflect = fast_rand();
			if(do_reflect < mat.reflectiveness)
			{
				t_v3d reflected = ft_v3d_reflect(ray.direction, c.hit_normal);
				t_v3d random_dir = ft_v3d_random_hemisphere(c.hit_normal);
				t_v3d new_dir = ft_v3d_normalize(ft_v3d_lerp(reflected, random_dir, mat.diffusion));
				ray = ft_setup_ray_direction(ray, new_dir, ray.remaining_bounces - 1);
				return (ft_get_pixel_color(ray, scene));
			}
			else
			{
				ray = ft_setup_ray_direction(ray, ft_v3d_random_hemisphere(c.hit_normal), ray.remaining_bounces - 1);
				c.light_color = ft_v3d_add(ft_get_light(c.hit_point, c.hit_normal, scene), ft_get_pixel_color(ray, scene));
				return (ft_v3d_mult(c.out_color, c.light_color));
			}
		}
		else // last bounce, just return the color
			c.out_color = ft_v3d_mult(c.out_color, ft_get_light(c.hit_point, c.hit_normal, scene));
		return (c.out_color);
	}
	return (ft_get_sky_color(ray));
}

