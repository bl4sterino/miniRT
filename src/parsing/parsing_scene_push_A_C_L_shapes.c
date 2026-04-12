/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_push_A_C_L_shapes.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:22:05 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 23:36:18 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_push_a(t_scene *scene, t_parsed_object *po)
{
	t_v3f	color;

	scene->ambient_light = po->object.as_ambient_light;
	color = ft_v3f_scale(scene->ambient_light.color,
			scene->ambient_light.intensity);
	scene->ambient_light.rgb_int_color = ft_v3f_to_int_color(color);
}

void	ft_push_c(t_scene *scene, t_parsed_object *po)
{
	po->object.as_camera.stereo_offset = -5.0f;
	po->object.as_camera.render_mode = RENDER_DEFAULT;
	po->object.as_camera.stereo = 0;
	ft_normalize_vector(&(po->object.as_camera.direction));
	if (po->object.as_camera.render_mode < 0
		|| po->object.as_camera.render_mode > RENDER_RAY_TARGETS)
		ft_exit_str_fd(1, "Camera render mode is out of range\n", 2);
	po->object.as_camera.stereo_space = DEFAULT_STEREO_HALF_SPACE;
	add_camera(scene, &po->object.as_camera);
}

void	ft_push_l(t_scene *scene, t_extraction_counts *c, t_parsed_object *po)
{
	scene->lights[c->lights] = po->object.as_light;
	scene->lights[c->lights].color
		= ft_v3f_scale(scene->lights[c->lights].color,
			scene->lights[c->lights].intensity);
	c->lights++;
}

void	ft_push_shapes(t_scene *scene, t_extraction_counts *counts,
		t_parsed_object *po)
{
	scene->raw_objects[counts->object].type = po->type;
	if (ft_abs(po->material.color_tex) > scene->num_textures
		|| ft_abs(po->material.normal_tex) > scene->num_textures)
		ft_exit_str_fd(1, "Ivalid texture index\n", 2);
	scene->raw_objects[counts->object].material = po->material;
	if (po->type == object_type_triangle)
		scene->raw_objects[counts->object].object.as_triangle
			= ft_get_processed_triangle(po->object.as_triangle);
	else if (po->type == object_type_sphere)
		scene->raw_objects[counts->object].object.as_sphere
			= po->object.as_sphere;
	else if (po->type == object_type_quad)
		scene->raw_objects[counts->object].object.as_quad
			= ft_get_processed_quad(po->object.as_quad);
	else if (po->type == object_type_cylinder)
	{
		ft_normalize_vector(&(po->object.as_cylinder.normal));
		scene->raw_objects[counts->object].object.as_cylinder
			= ft_get_processed_cylinder(po->object.as_cylinder);
	}
	else if (po->type == object_type_ellipsoid)
		scene->raw_objects[counts->object].object.as_ellipsoid
			= ft_get_processed_ellipsoid(po->object.as_ellipsoid);
	scene->raw_objects[counts->object].raw_id = counts->object;
	counts->object++;
}
