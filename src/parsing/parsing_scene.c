/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:36:43 by pberne            #+#    #+#             */
/*   Updated: 2026/01/21 20:23:36 by pberne           ###   ########.fr       */
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

long ft_count_matches(t_list *lst, t_object_type type)
{
	t_object_element *elem;
	long count = 0;

	while (lst)
	{
		elem = lst->content;
		if (elem->type == type)
			count++;
		lst = lst->next;
	}
	return (count);
}

t_scene *ft_fill_scene(t_scene *scene, t_list *lst)
{
	
}

t_scene	*ft_build_scene_from_elements(t_list *lst)
{
	t_scene	*scene;
	void	*ptr;
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
	scene_size += sizeof(t_cylinder) * ft_count_matches(lst, object_type_cylinder);
	scene = ft_malloc(scene_size);
	return (ft_fill_scene(scene, lst));	
}

t_scene	*ft_parse_map(char *finename)
{
	t_scene_parsing_context	context;

	ft_bzero(&context, sizeof(context));
	context.fd = open(finename, O_RDONLY);
	if (context.fd == -1)
		return (0);
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
				return (0);
		}
		ft_free(context.line);
		context.line = get_next_line_gc(context.fd);
	}
	return (ft_build_scene_from_elements(context.object_lst));
}
