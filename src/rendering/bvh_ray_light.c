/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_ray_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:41:45 by pberne            #+#    #+#             */
/*   Updated: 2026/03/01 11:10:54 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"



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

float	ft_get_object_area(t_object object)
{
	if (object.type == object_type_sphere)
		return (ft_sphere_area(object.object.as_sphere));
	else if (object.type == object_type_cylinder)
		return (ft_cylinder_area(object.object.as_cylinder));
	else if (object.type == object_type_quad)
		return (ft_quad_area(object.object.as_quad));
	else if (object.type == object_type_triangle)
		return (ft_triangle_area(object.object.as_triangle));
	return (1.0f);
}

t_v3f	ft_get_light(t_v3f position, t_v3f normal, t_scene *scene)
{
	t_get_light_context	c;

	c.i = -1;
	c.color = scene->ambient_light.color;
	c.light_ray.origin = position;
	while (++c.i < scene->num_lights)
	{
		c.light_ray = ft_setup_ray_target(c.light_ray,
				scene->lights[c.i].position, 0);
		if (ft_v3f_dot(normal, c.light_ray.direction) < 0.0f)
			continue ;
		c.light_dist = ft_v3f_length(ft_v3f_sub(scene->lights[c.i].position,
					c.light_ray.origin));
		c.plane_dist = ft_shoot_ray_against_planes(c.light_ray, c.light_dist,
				scene, &c.hit);
		if (c.plane_dist < c.light_dist)
			continue ;
		c.dist = ft_shoot_ray_against_objects(c.light_ray, c.light_dist, scene,
				&c.hit);
		if (c.dist >= c.light_dist)
		{
			c.new_color = ft_v3f_scale(scene->lights[c.i].color,
					ft_v3f_dot(c.light_ray.direction, normal));
			c.color = ft_v3f_add(c.color, c.new_color);
		}
	}
	
	if (scene->emissive_objects > 0)
	{
		int rand_emissive = (int)(fast_rand() * (float)scene->emissive_objects) % scene->emissive_objects;
		t_object obj = scene->raw_objects[rand_emissive];
		c.light_ray = ft_setup_ray_target(c.light_ray, ft_get_random_point_on_object(obj), 0);
		float emission_dot = ft_v3f_dot(c.light_ray.direction, normal);
		if (emission_dot < 0.0f)
			return (c.color);
			
		c.dist = ft_shoot_ray_against_objects(c.light_ray, INFINITY, scene, &c.hit);
		if (c.dist < INFINITY)
		{
			int raw_hit = scene->objects[c.hit].raw_id;
			if(raw_hit == rand_emissive)
			{
				c.dist = fmaxf(c.dist * c.dist, 1.0f);
				float emission_surface_coef;
				if (obj.type == object_type_sphere)
					emission_surface_coef = 1.0f;
				else
					emission_surface_coef = fabsf(ft_v3f_dot(ft_v3f_scale(c.light_ray.direction, -1.0f), obj.object.as_quad.normal));

				float geom_term = (emission_dot * emission_surface_coef) / c.dist;

				float area = ft_get_object_area(obj);
				float pdf = (1.0f / area) * (1.0f / (float)scene->emissive_objects);
				float weigh = (geom_term / (pdf * PI));

				t_v3f max = ft_v3f_scale(obj.material.color, obj.material.emission);
				t_v3f targeted_light = ft_v3f_scale(obj.material.color, weigh * obj.material.emission);
				targeted_light.x = fminf(targeted_light.x, max.x);
				targeted_light.y = fminf(targeted_light.y, max.y);
				targeted_light.z = fminf(targeted_light.z, max.z);
				c.color = ft_v3f_add(c.color, targeted_light);
			}
		}
	}

	return (c.color);
}
