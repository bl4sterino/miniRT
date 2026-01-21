/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:36:43 by pberne            #+#    #+#             */
/*   Updated: 2026/01/21 15:31:10 by pberne           ###   ########.fr       */
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

t_list	*ft_parse_map(char *finename)
{
	t_scene_parsing_context	context;

	ft_bzero(&context, sizeof(context));
	context.fd = open(finename, O_RDONLY);
	if (context.fd == -1)
		return (context.object_lst);
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
	return (context.object_lst);
}
