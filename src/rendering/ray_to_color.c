/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:57:51 by pberne            #+#    #+#             */
/*   Updated: 2026/03/02 19:52:58 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline t_v3f	ft_get_sky_color(t_ray ray)
{
	float	dot;

	dot = (float)ft_v3f_dot(ray.direction, (t_v3f){{0.0f, 1.0f, 0.0f}});
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
t_v3f	ft_get_pixel_color(t_ray ray, t_scene *scene, t_v3f *hit_normal, t_v3f *hit_pos)
{
	t_pixel_color_context	c;

	c.out_color = (t_v3f){{0.0f, 0.0f, 0.0f}};
	c.distance = ft_shoot_ray(ray, scene, &c.hit);

	// fog
	/*if(ray.remaining_bounces > 0)
	{
		float scatter_dist = -log((double)fmaxf(fast_rand(), EPSILON)) / 0.001;
		if (scatter_dist < c.distance)
		{
			ray.origin = ft_ray_at(ray, scatter_dist);
			//c.out_color = ft_get_light(ray.origin, (t_v3f){{0.0f, 0.0f, 0.0f}}, scene);

			ray = ft_setup_ray_direction(ray, ft_v3f_random(), ray.remaining_bounces - 1);

			c.out_color = ft_v3f_add(c.out_color, ft_get_pixel_color(ray, scene, hit_normal, hit_pos));
			return (c.out_color);
		}
	}*/

	if (c.distance < INFINITY)
	{
		if (c.hit < 0)
			c.mat = scene->planes[-c.hit - 1].material;
		else
			c.mat = scene->objects[c.hit].material;

		
		// Replace that with proper hit detection outputtin both point and normal
		c.hit_point = ft_ray_at(ray, c.distance - EPSILON);
		c.hit_normal = ft_get_hit_normal(c.hit_point, scene, c.hit, ray.direction);
		c.hit_point = ft_v3f_add(ft_ray_at(ray, c.distance), ft_v3f_scale(c.hit_normal, EPSILON));
		
		if(hit_normal)
		{
			*hit_normal = c.hit_normal;
			*hit_pos = c.hit_point;
		}

		if (c.mat.emission > 0.0f)
			return (ft_v3f_scale(c.mat.color, c.mat.emission));
			

		c.out_color = c.mat.color;
		if (c.mat.refraction > 0.0f)
			{
				char side = ft_get_hit_side(scene, c.hit_point, c.hit);
			
				float ref_from = tn_f(side > 0, 1.0f, c.mat.refraction);
 				float ref_to = tn_f(side > 0, c.mat.refraction, 1.0f);


				if (c.mat.diffusion > 0.0f)
					c.reflected = ft_v3f_normalize(ft_v3f_lerp(c.hit_normal, ft_v3f_random_hemisphere(c.hit_normal), c.mat.diffusion));
				else
					c.reflected = c.hit_normal;
				c.new_dir = ft_v3f_refract(ray.direction, c.reflected, ref_from, ref_to);
				if (c.new_dir.x != 0.0f || c.new_dir.y != 0.0f || c.new_dir.z != 0.0f)
				{
					ray.origin = ft_v3f_add(ft_ray_at(ray, c.distance), ft_v3f_scale(c.new_dir, EPSILON));
					 // VERY DANGEROUS to not decrease the bounce count, maybe have some kind of credit for refraction
					ray = ft_setup_ray_direction(ray, c.new_dir, ray.remaining_bounces);
					return (ft_v3f_mult(c.mat.color, ft_get_pixel_color(ray, scene, hit_normal, hit_pos)));
				}

				c.mat.reflectiveness_rand = -1.0f;
				c.mat.diffusion = 0.0f;
			}
		if (ray.remaining_bounces > 0)
		{
			ray.origin = c.hit_point;
			if(c.mat.reflectiveness_rand < c.mat.reflectiveness)
			{
				c.reflected = ft_v3f_reflect(ray.direction, c.hit_normal);
				c.new_dir = ft_v3f_lerp(c.reflected, ft_v3f_random_hemisphere(c.hit_normal), c.mat.diffusion);
				ray = ft_setup_ray_direction(ray, c.new_dir, ray.remaining_bounces - 1);
				return (ft_get_pixel_color(ray, scene, hit_normal, hit_pos));
			}
			else // Indirect lighting / diffusion
			{
				t_v3f direct_light = ft_get_light(c.hit_point, c.hit_normal, scene);

				ray = ft_setup_ray_direction(ray, ft_v3f_random_hemisphere(c.hit_normal), ray.remaining_bounces - 1);
				t_v3f indirect_light = ft_get_pixel_color(ray, scene, 0, 0);
				float bounce_weight = ft_v3f_dot(c.hit_normal, ray.direction);
				//indirect_light = ft_v3f_scale(indirect_light, bounce_weight);
				
				c.light_color = ft_v3f_add(direct_light, indirect_light);
				return (ft_v3f_mult(c.out_color, c.light_color));
			}
		}
		else
			c.out_color = ft_v3f_mult(c.out_color, ft_get_light(c.hit_point, c.hit_normal, scene));
		return (c.out_color);
	}
	if(hit_normal)
	{
		*hit_normal = ray.direction;
		*hit_pos = (t_v3f){{15000.0f, 15000.0f, 15000.0f}};
	}
	return (ft_get_sky_color(ray));
}

