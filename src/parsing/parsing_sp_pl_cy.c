/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sp_pl_cy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:49:58 by pberne            #+#    #+#             */
/*   Updated: 2026/01/29 17:07:11 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_struct_parser_data	*ft_get_parser_sphere(int id)
{
	t_list					*lst;
	t_parsing_data			d;
	t_struct_parser_data	*struct_parser;

	struct_parser = ft_malloc_id(sizeof(t_struct_parser_data), id);
	struct_parser->type = object_type_sphere;
	lst = 0;
	d = (t_parsing_data){p_double, offsetof(t_sphere, position.x), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_sphere, position.y), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_sphere, position.z), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double, offsetof(t_sphere, radius), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_sphere, color.x), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_sphere, color.y), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_sphere, color.z), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_try_or_0, offsetof(t_sphere, reflection), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	struct_parser->element_lst = lst;
	struct_parser->material_lst = NULL;
	return (struct_parser);
}

t_struct_parser_data	*ft_get_parser_plane2(int id, t_list *lst,
		t_parsing_data d, t_struct_parser_data *struct_parser)
{
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_plane, color.x), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_plane, color.y), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_plane, color.z), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_try_or_0, offsetof(t_plane, reflection), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	struct_parser->element_lst = lst;
	struct_parser->material_lst = NULL;
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
	return (ft_get_parser_plane2(id, lst, d, struct_parser));
}

t_struct_parser_data	*ft_get_parser_cylinder2(int id, t_list *lst,
		t_parsing_data d, t_struct_parser_data *struct_parser)
{
	d = (t_parsing_data){p_double, offsetof(t_cylinder, height), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_cylinder, color.x),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_cylinder, color.y),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_0_255_to_0_1, offsetof(t_cylinder, color.z),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_try_or_0, offsetof(t_cylinder, reflection),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	struct_parser->element_lst = lst;
	struct_parser->material_lst = NULL;
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
