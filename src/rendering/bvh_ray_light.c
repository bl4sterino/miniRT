/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_ray_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:41:45 by pberne            #+#    #+#             */
/*   Updated: 2026/03/05 15:57:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// TODO proper random points

/* Gets direct light from spot lights */
t_v3f	ft_get_spot_light_color(t_v3f position, t_v3f normal, t_scene *scene)
{
	t_get_light_context	c;

	c.rand_light = (int)(fast_rand() * (float)scene->num_lights)
		% scene->num_lights;
	c.light = scene->lights[c.rand_light];
	c.light_ray.origin = position;
	c.light_ray = ft_setup_ray_target(c.light_ray, c.light.position, 0);
	if (ft_v3f_dot(normal, c.light_ray.direction) < 0.0f)
		return ((t_v3f){{0.0f, 0.0f, 0.0f}});
	c.light_dist = ft_v3f_length(ft_v3f_sub(c.light.position,
				c.light_ray.origin));
	c.plane_dist = ft_shoot_ray_against_planes(c.light_ray, c.light_dist, scene,
			&c.hit);
	if (c.plane_dist < c.light_dist)
		return ((t_v3f){{0.0f, 0.0f, 0.0f}});
	c.dist = ft_shoot_ray_against_objects(c.light_ray, c.light_dist, scene,
			&c.hit);
	if (c.dist >= c.light_dist)
	{
		c.new_color = ft_v3f_scale(c.light.color,
				ft_v3f_dot(c.light_ray.direction, normal)
				* (float)scene->num_lights);
		return (c.new_color);
	}
	return ((t_v3f){{0.0f, 0.0f, 0.0f}});
}

static inline float	ft_get_emission_coef(t_object obj, t_ray light_ray)
{
	if (obj.type == object_type_sphere)
		return (1.0f);
	else if (obj.type == object_type_quad)
		return (fabsf(ft_v3f_dot(ft_v3f_scale(light_ray.direction, -1.0f),
					obj.object.as_quad.normal)));
	else if (obj.type == object_type_triangle)
		return (fabsf(ft_v3f_dot(ft_v3f_scale(light_ray.direction, -1.0f),
					obj.object.as_triangle.normal)));
	else
		return (1.0f);
}

static inline t_v3f	ft_get_emissive_light(t_get_emissive_light_context *c)
{
	c->dist = fmaxf(c->dist * c->dist, 1.0f);
	c->emission_surface_coef = ft_get_emission_coef(c->obj, c->light_ray);
	c->geom_term = (c->emission_dot * c->emission_surface_coef) / c->dist;
	c->weigh = c->geom_term / c->obj.pdf;
	c->targeted_light = ft_v3f_scale(c->obj.material.color, c->weigh);
	c->targeted_light = ft_v3f_min(c->targeted_light, c->obj.material.color);
	return (c->targeted_light);
}

/* gets light from emissive objects */
t_v3f	ft_get_emissive_light_color(t_v3f position, t_v3f normal,
		t_scene *scene)
{
	t_get_emissive_light_context	c;

	c.rand_emissive = (int)(fast_rand() * (float)scene->emissive_objects)
		% scene->emissive_objects;
	c.obj = scene->raw_objects[c.rand_emissive];
	c.bypass_normal = (normal.x == 0.0f && normal.y == 0.0f
			&& normal.z == 0.0f);
	c.light_ray.origin = position;
	c.light_ray = ft_setup_ray_target(c.light_ray,
			ft_get_random_point_on_object(c.obj), 5);
	c.emission_dot = tn_f(c.bypass_normal, 1.0f,
			ft_v3f_dot(c.light_ray.direction, normal));
	if (c.emission_dot < 0.0f)
		return ((t_v3f){{0.0f, 0.0f, 0.0f}});
	c.dist = ft_shoot_ray(c.light_ray, scene, &c.hit);
	if (c.dist < INFINITY && c.hit >= 0)
	{
		c.raw_hit = scene->objects[c.hit].raw_id;
		if (c.raw_hit == c.rand_emissive)
			return (ft_get_emissive_light(&c));
	}
	return ((t_v3f){{0.0f, 0.0f, 0.0f}});
}

t_v3f	ft_get_light(t_v3f position, t_v3f normal, t_scene *scene)
{
	t_v3f	light_color;

	light_color = scene->ambient_light.color;
	if (scene->num_lights > 0)
		light_color = ft_v3f_add(light_color, ft_get_spot_light_color(position,
					normal, scene));
	if (scene->emissive_objects > 0)
		light_color = ft_v3f_add(light_color,
				ft_get_emissive_light_color(position, normal, scene));
	return (light_color);
}
