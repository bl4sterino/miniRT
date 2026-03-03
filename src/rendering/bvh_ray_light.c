/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_ray_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:41:45 by pberne            #+#    #+#             */
/*   Updated: 2026/03/03 17:11:22 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


// TODO proper random points
t_v3f	ft_get_random_point_on_object(t_object object)
{
	if (object.type == object_type_sphere)
	{
		t_v3f rand_dir = ft_v3f_normalize(ft_v3f_random());
		return (ft_v3f_add(object.object.as_sphere.position,
			ft_v3f_scale(rand_dir, object.object.as_sphere.radius - EPSILON * 2.0f)));
	}
	else if (object.type == object_type_cylinder)
		return (object.object.as_cylinder.position);
	else if (object.type == object_type_quad)
	{
		t_v3f ret = object.object.as_quad.position;
		t_v3f u_rand = ft_v3f_scale(object.object.as_quad.u_axis, (object.object.as_quad.size.x * (0.5f - EPSILON)) * (fast_rand() * 2.0f - 1.0f));
		t_v3f v_rand = ft_v3f_scale(object.object.as_quad.v_axis, (object.object.as_quad.size.y * (0.5f - EPSILON)) * (fast_rand() * 2.0f - 1.0f));
		return ((t_v3f){{ret.x + u_rand.x + v_rand.x, ret.y + u_rand.y + v_rand.y, ret.z + u_rand.z + v_rand.z}});
	}
	else if (object.type == object_type_triangle)
		return (object.object.as_triangle.position);
	return ((t_v3f){{0.0f, 0.0f, 0.0f}});
}

/* Gets direct light from spot lights */
t_v3f ft_get_spot_light_color(t_v3f position, t_v3f normal, t_scene *scene)
{
	t_get_light_context c;

	int rand_light = (int)(fast_rand() * (float)scene->num_lights) % scene->num_lights;

	t_light light = scene->lights[rand_light];
	c.light_ray.origin = position;
	c.light_ray = ft_setup_ray_target(c.light_ray,
				light.position, 0);
	if (ft_v3f_dot(normal, c.light_ray.direction) < 0.0f)
		return ((t_v3f){{0.0f, 0.0f, 0.0f}});
	c.light_dist = ft_v3f_length(ft_v3f_sub(light.position,
				c.light_ray.origin));
	c.plane_dist = ft_shoot_ray_against_planes(c.light_ray, c.light_dist,
			scene, &c.hit);
	if (c.plane_dist < c.light_dist)
		return ((t_v3f){{0.0f, 0.0f, 0.0f}});
	c.dist = ft_shoot_ray_against_objects(c.light_ray, c.light_dist, scene,
			&c.hit);
	if (c.dist >= c.light_dist)
	{
		c.new_color = ft_v3f_scale(light.color,
				ft_v3f_dot(c.light_ray.direction, normal) * (float)scene->num_lights);
		return (c.new_color);
	}
	return ((t_v3f){{0.0f, 0.0f, 0.0f}});
}

float ft_shoot_light_ray(t_ray ray, t_scene *scene, int *out_hit, t_v3f *filtered_light)
{
	float total_dist;
	float dist;
	int hit;
	t_v3f hit_point;
	t_v3f hit_normal;
	t_v3f reflected;
	t_v3f new_dir;

	total_dist = 0.0f;
	*filtered_light = (t_v3f){{1.0f, 1.0f, 1.0f}};
	while (ray.remaining_bounces > 0)
	{
		dist = ft_shoot_ray(ray, scene, &hit);
		if (dist == INFINITY)
			return (INFINITY);
		total_dist += dist;
		*out_hit = hit;
		return (total_dist);
		/*t_material mat = scene->objects[hit].material;
		if (mat.refraction > 0.0f)
		{
			*filtered_light = ft_v3f_mult(*filtered_light, mat.color);
			hit_point = ft_ray_at(ray, dist - EPSILON);
			hit_normal = ft_get_hit_normal(hit_point, scene, hit, ray.direction);
			hit_point = ft_v3f_add(ft_ray_at(ray, dist), ft_v3f_scale(hit_normal, EPSILON));


			char side = ft_get_hit_side(scene, hit_point, hit);
			float ref_from = tn_f(side > 0, 1.0f, mat.refraction);
 			float ref_to = tn_f(side > 0, mat.refraction, 1.0f);


			if (mat.diffusion > 0.0f)
				reflected = ft_v3f_normalize(ft_v3f_lerp(hit_normal, ft_v3f_random_hemisphere(hit_normal), mat.diffusion));
			else
				reflected = hit_normal;
			new_dir = ft_v3f_refract(ray.direction, reflected, ref_from, ref_to);
			if (new_dir.x != 0.0f || new_dir.y != 0.0f || new_dir.z != 0.0f)
			{
				ray.origin = ft_v3f_add(ft_ray_at(ray, dist), ft_v3f_scale(new_dir, EPSILON));
				// VERY DANGEROUS to not decrease the bounce count, maybe have some kind of credit for refraction
				ray = ft_setup_ray_direction(ray, new_dir, ray.remaining_bounces - 1);
				continue;
			}
			else
				return (total_dist);
		}
		else
			return(total_dist);*/
	}
	return (total_dist);
}

/* gets light from emissive objects */
t_v3f ft_get_emissive_light_color(t_v3f position, t_v3f normal, t_scene *scene)
{
	t_ray light_ray;
	int hit;
	
	int rand_emissive = (int)(fast_rand() * (float)scene->emissive_objects) % scene->emissive_objects;
	t_object obj = scene->raw_objects[rand_emissive];

	char bypass_normal;

	bypass_normal = (normal.x == 0.0f && normal.y == 0.0f && normal.z == 0.0f);


	light_ray.origin = position;
	light_ray = ft_setup_ray_target(light_ray, ft_get_random_point_on_object(obj), 5);
	float emission_dot = tn_f(bypass_normal, 1.0f, ft_v3f_dot(light_ray.direction, normal));
	if (emission_dot < 0.0f)
		return ((t_v3f){{0.0f, 0.0f, 0.0f}});
	
	//float dist = ft_shoot_light_ray(light_ray, scene, &hit);

	float dist = ft_shoot_ray(light_ray, scene, &hit);
	if (dist < INFINITY && hit >= 0)
	{
		int raw_hit = scene->objects[hit].raw_id;
		if(raw_hit == rand_emissive)
		{
			dist = fmaxf(dist * dist, 1.0f);
			float emission_surface_coef;
			if (obj.type == object_type_sphere)
				emission_surface_coef = 1.0f;
			else
				emission_surface_coef = fabsf(ft_v3f_dot(ft_v3f_scale(light_ray.direction, -1.0f), obj.object.as_quad.normal));
			// TOTO, other shapes
			float geom_term = (emission_dot * emission_surface_coef) / dist;
			float weigh = geom_term / obj.pdf;
			t_v3f max = ft_v3f_scale(obj.material.color, obj.material.emission);
			t_v3f targeted_light = ft_v3f_scale(obj.material.color, weigh * obj.material.emission);
			targeted_light.x = fminf(targeted_light.x, max.x);
			targeted_light.y = fminf(targeted_light.y, max.y);
			targeted_light.z = fminf(targeted_light.z, max.z);
			return (targeted_light);
		}
	}
	return ((t_v3f){{0.0f, 0.0f, 0.0f}});
}

t_v3f	ft_get_light(t_v3f position, t_v3f normal, t_scene *scene)
{
	t_v3f light_color;

	light_color = scene->ambient_light.color;
	if (scene->num_lights > 0)
		light_color = ft_v3f_add(light_color, ft_get_spot_light_color(position, normal, scene));
	if (scene->emissive_objects > 0)
		light_color = ft_v3f_add(light_color, ft_get_emissive_light_color(position, normal, scene));
	return (light_color);
}
