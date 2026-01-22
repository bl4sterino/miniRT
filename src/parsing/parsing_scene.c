/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:36:43 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 14:52:01 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_parse_line(char **strs, t_dict *dict, int malloc_id, t_list **object_lst)
{
	t_object_element		*new_object;
	t_struct_parser_data	*parser;

	parser = ft_dict_get(dict, strs[0]);
	if (!parser)
		return (0);
	new_object = ft_malloc_id(sizeof(t_object_element), malloc_id);
	new_object->type = parser->type;
	ft_lstadd_back(object_lst, ft_lstnew_gc_id(new_object, malloc_id));
	return (ft_parse_data(strs + 1, &new_object->object, parser->lst,
			malloc_id));
	return (0);
}

long	ft_count_matches(t_list *lst, t_object_type type)
{
	t_object_element	*elem;
	long				count;

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
	scene->spheres = (t_sphere *)(((char *)scene) + sizeof(t_scene));
	scene->planes = (t_plane *)(((char *)scene->spheres) + sizeof(t_sphere)
			* scene->num_spheres);
	scene->cylinders = (t_cylinder *)(((char *)scene->planes) + sizeof(t_plane)
			* scene->num_planes);
	scene->lights = (t_light *)(((char *)scene->cylinders) + sizeof(t_cylinder)
			* scene->num_cylinders);
	ft_extract_camera(scene, lst);
	ft_extract_ambient_light(scene, lst);
	ft_extract_lights(scene, lst);
	ft_extract_spheres(scene, lst);
	ft_extract_planes(scene, lst);
	ft_extract_cylinder(scene, lst);
	ft_normalize_vectors(scene);
	return (scene);
}

// TODO : try memory allignment ?

t_scene	*ft_build_scene_from_elements(t_list *lst)
{
	t_scene	*scene;
	long	scene_size;

	if (ft_count_matches(lst, object_type_ambient_light) != 1)
		return (0);
	if (ft_count_matches(lst, object_type_camera) != 1)
		return (0);
	if (ft_count_matches(lst, object_type_light) != 1)
		return (0);
	scene_size = sizeof(t_camera) + sizeof(t_ambient_light) + sizeof(t_light);
	scene_size += sizeof(t_scene);
	scene_size += sizeof(t_sphere) * ft_count_matches(lst, object_type_sphere);
	scene_size += sizeof(t_plane) * ft_count_matches(lst, object_type_plane);
	scene_size += sizeof(t_cylinder) * ft_count_matches(lst,
			object_type_cylinder);
	scene = ft_malloc(scene_size);
	scene->num_spheres = ft_count_matches(lst, object_type_sphere);
	scene->num_planes = ft_count_matches(lst, object_type_plane);
	scene->num_cylinders = ft_count_matches(lst, object_type_cylinder);
	scene->num_lights = ft_count_matches(lst, object_type_light);
	return (ft_fill_scene(scene, lst));
}

t_scene	*ft_parse_map(char *finename)
{
	t_scene_parsing_context	context;

	ft_bzero(&context, sizeof(context));
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
			context.line_count += 1;
		}
		ft_free(context.line);
		context.line = get_next_line_gc(context.fd);
	}
	return (ft_build_scene_from_elements(context.object_lst));
}
