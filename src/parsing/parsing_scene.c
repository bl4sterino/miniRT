/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:36:43 by pberne            #+#    #+#             */
/*   Updated: 2026/01/31 13:19:18 by pberne           ###   ########.fr       */
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
		return (0);
	new_object = ft_malloc_id(sizeof(t_parsed_object), malloc_id);
	ft_bzero(new_object, sizeof(t_parsed_object));
	new_object->type = parser->type;
	ft_lstadd_back(object_lst, ft_lstnew_gc_id(new_object, malloc_id));
	element_parsed = ft_parse_data(strs + 1, &new_object->object,
			parser->element_lst, malloc_id);
	if (element_parsed > 0 && parser->material_lst)
	{
		result = ft_parse_data(strs + element_parsed + 1, &new_object->material,
				parser->material_lst, malloc_id);
		return (result);
	}
	else
		return (element_parsed);
}

long	ft_count_matches(t_list *lst, t_object_type type)
{
	t_parsed_object	*elem;
	long			count;

	count = 0;
	while (lst)
	{
		elem = lst->content;
		if (elem->type == type)
			count++;
		lst = lst->next;
	}
	return (count);
}

t_scene	*ft_fill_scene(t_scene *scene, t_list *lst)
{
	ft_normalize_vectors(lst);
	ft_extract_camera(scene, lst);
	ft_extract_ambient_light(scene, lst);
	ft_extract_planes(scene, lst);
	ft_extract_lights(scene, lst);
	ft_extract_objects(scene, lst);
	ft_process_objects_bounds(scene);
	scene->bvh_node_capacity = scene->num_objects * 2;
	scene->bvh_nodes = ft_malloc(sizeof(t_bvh_node) * scene->bvh_node_capacity);
	scene->bvh_node_count = 0;
	scene->bvh_root = ft_bvh_builder(scene, 0, scene->num_objects);
	return (scene);
}

t_scene	*ft_build_scene_from_elements(t_list *lst)
{
	t_scene	*scene;

	if (ft_count_matches(lst, object_type_ambient_light) != 1)
		ft_exit_str_fd(1, "Ambient Light is missing\n", 2);
	if (ft_count_matches(lst, object_type_camera) != 1)
		ft_exit_str_fd(1, "Camera is missing\n", 2);
	if (ft_count_matches(lst, object_type_light) < 1)
		ft_exit_str_fd(1, "Point Light is missing\n", 2);
	scene = ft_malloc(sizeof(t_scene));
	ft_bzero(scene, sizeof(t_scene));
	scene->planes = ft_malloc(sizeof(t_object) * ft_count_matches(lst,
				object_type_plane));
	scene->lights = ft_malloc(sizeof(t_light) * ft_count_matches(lst,
				object_type_light));
	return (ft_fill_scene(scene, lst));
}

t_scene	*ft_parse_map(char *finename)
{
	t_scene_parsing_context	context;

	ft_bzero(&context, sizeof(context));
	context.line_count = 1;
	context.fd = open(finename, O_RDONLY);
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
	return (ft_build_scene_from_elements(context.object_lst));
}
