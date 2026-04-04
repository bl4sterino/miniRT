/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_skybox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 10:54:06 by pberne            #+#    #+#             */
/*   Updated: 2026/04/04 15:23:11 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_struct_parser_data	*ft_get_parser_skybox(int id)
{
	t_list					*lst;
	t_parsing_data			d;
	t_struct_parser_data	*struct_parser;

	struct_parser = ft_malloc_id(sizeof(t_struct_parser_data), id);
	struct_parser->type = object_type_skybox;
	lst = 0;
	d = (t_parsing_data){p_int, offsetof(t_skybox, color), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_int, offsetof(t_skybox, luminance), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	struct_parser->element_lst = lst;
	struct_parser->material_lst = NULL;
	return (struct_parser);
}
