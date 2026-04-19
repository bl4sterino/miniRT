/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:36:43 by pberne            #+#    #+#             */
/*   Updated: 2026/04/19 18:05:06 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_parse_line(char **strs, t_dict *dict, int malloc_id, t_list **object_lst)
{
	t_parsed_object			*new_object;
	t_struct_parser_data	*parser;
	int						element_parsed;
	int						result;

	parser = ft_dict_get(dict, strs[0]);
	if (!parser)
		return (ft_try_parse_texture(strs, malloc_id, object_lst));
	new_object = ft_malloc_id(sizeof(t_parsed_object), malloc_id);
	ft_bzero(new_object, sizeof(t_parsed_object));
	new_object->type = parser->type;
	ft_lstadd_front(object_lst, ft_lstnew_gc_id(new_object, malloc_id));
	element_parsed = ft_parse_data(strs + 1, &new_object->object,
			parser->element_lst, malloc_id);
	if (element_parsed > 0 && parser->material_lst)
	{
		result = ft_parse_data(strs + element_parsed + 1, &new_object->material,
				parser->material_lst, malloc_id);
		return (ft_free_split_gc(strs), result);
	}
	else
		return (ft_free_split_gc(strs), element_parsed);
}

void	ft_print_scene_slements_count(int *counts)
{
	if (counts[object_type_light] > 0)
		ft_printf("lights: %d\n", counts[object_type_light]);
	if (counts[object_type_sphere] > 0)
		ft_printf("spheres: %d\n", counts[object_type_sphere]);
	if (counts[object_type_cylinder] > 0)
		ft_printf("cylinders: %d\n", counts[object_type_cylinder]);
	if (counts[object_type_quad] > 0)
		ft_printf("quads: %d\n", counts[object_type_quad]);
	if (counts[object_type_ellipsoid] > 0)
		ft_printf("ellipsoids: %d\n", counts[object_type_ellipsoid]);
	if (counts[object_type_triangle] > 0)
		ft_printf("triangles: %d\n", counts[object_type_triangle]);
	if (counts[object_type_texture_path] > 0)
		ft_printf("textures: %d\n", counts[object_type_texture_path]);
}

t_scene	*ft_fill_scene(t_data *d, t_scene *scene, t_list *lst, int *counts)
{
	ft_allocate_scene_data(scene, counts);
	ft_extract_scene_data(d, scene, lst, counts[object_type_texture_path]);
	ft_setup_emissive_objects(scene);
	ft_process_objects_bounds(scene);
	ft_print_scene_slements_count(counts);
	ft_printf("Parsing: %f\n", ft_clock_set_and_get(clock_loading));
	ft_clock_start(clock_loading);
	scene->bvh_root = ft_update_bvh(scene, 0, scene->num_objects);
	ft_printf("BVH: %f\n", ft_clock_set_and_get(clock_loading));
	d->target_ray_bounces = scene->ambient_light.ray_bounce;
	scene->render_ui = 1;
	return (scene);
}

t_scene	*ft_build_scene_from_elements(t_data *d, t_list *lst)
{
	t_scene	*scene;
	int		counts[11];

	ft_memset_int(counts, 0, object_type_count);
	ft_count_matches(lst, counts);
	if (counts[object_type_ambient_light] != 1)
		ft_exit_str_fd(1, "Wrong number of Ambient Light\n", 2);
	if (counts[object_type_skybox] > 1)
		ft_exit_str_fd(1, "Too many skyboxes\n", 2);
	if (counts[object_type_camera] == 0)
		ft_exit_str_fd(1, "No cameras\n", 2);
	scene = ft_malloc_id(sizeof(t_scene), malloc_id_scene);
	ft_bzero(scene, sizeof(t_scene));
	return (ft_fill_scene(d, scene, lst, counts));
}

t_scene	*ft_parse_map(t_data *d, char *filename)
{
	t_scene_parsing_context	context;

	ft_array_parser(d, filename);

	ft_bzero(&context, sizeof(context));
	context.line_count = 1;
	context.fd = open(filename, O_RDONLY);
	if (context.fd == -1)
		ft_exit_str_fd(EXIT_FAILURE, "Failed to open map\n", 2);
	ft_add_exit(ft_malloc_int(context.fd), ft_exit_close_fd);
	context.dict = ft_setup_parsing_dict(context.dict, malloc_id_parsing);
	context.line = get_next_line_gc(context.fd);
	while (context.line)
	{
		ft_str_replace(context.line, ",\t\n", ' ');
		context.strs = ft_split_gc_id(context.line, ' ', malloc_id_parsing);
		if (context.strs[0])
		{
			if (!ft_parse_line(context.strs, context.dict, malloc_id_parsing,
					&(context.object_lst)))
				ft_parsing_error_on_line(context.line_count);
		}
		context.line_count += 1;
		ft_free(context.line);
		context.line = get_next_line_gc(context.fd);
	}
	return (ft_build_scene_from_elements(d, context.object_lst));
}
