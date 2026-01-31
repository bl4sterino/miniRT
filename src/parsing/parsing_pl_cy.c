/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pl_cy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:49:58 by pberne            #+#    #+#             */
/*   Updated: 2026/01/31 17:42:40 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_struct_parser_data	*ft_get_parser_plane2(int id,
		t_struct_parser_data *struct_parser)
{
	t_list			*lst;
	t_parsing_data	d;

	lst = 0;
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_material, color.x),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_material, color.y),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_material, color.z),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_try_or_0, offsetof(t_material, reflection),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	struct_parser->material_lst = lst;
	return (struct_parser);
}

t_struct_parser_data	*ft_get_parser_plane(int id)
{
	t_list					*lst;
	t_parsing_data			d;
	t_struct_parser_data	*struct_parser;

	struct_parser = ft_malloc_id(sizeof(t_struct_parser_data), id);
	struct_parser->type = object_type_plane;
	lst = 0;
	d = (t_parsing_data){p_double, offsetof(t_plane, position.x), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_plane, position.y), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_plane, position.z), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_plane, normal.x), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_plane, normal.y), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_plane, normal.z), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	struct_parser->element_lst = lst;
	return (ft_get_parser_plane2(id, struct_parser));
}

t_struct_parser_data	*ft_get_parser_cylinder2(int id, t_list *lst,
		t_parsing_data d, t_struct_parser_data *struct_parser)
{
	d = (t_parsing_data){p_double, offsetof(t_cylinder, height), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	struct_parser->element_lst = lst;
	lst = 0;
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_material, color.x),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_material, color.y),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_material, color.z),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_try_or_0, offsetof(t_material, reflection),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	struct_parser->material_lst = lst;
	return (struct_parser);
}

t_struct_parser_data	*ft_get_parser_cylinder(int id)
{
	t_list					*lst;
	t_parsing_data			d;
	t_struct_parser_data	*struct_parser;

	struct_parser = ft_malloc_id(sizeof(t_struct_parser_data), id);
	struct_parser->type = object_type_cylinder;
	lst = 0;
	d = (t_parsing_data){p_double, offsetof(t_cylinder, position.x), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_cylinder, position.y), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_cylinder, position.z), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_cylinder, normal.x), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_cylinder, normal.y), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_cylinder, normal.z), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_cylinder, diameter), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	return (ft_get_parser_cylinder2(id, lst, d, struct_parser));
}
