/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_q.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:49:58 by pberne            #+#    #+#             */
/*   Updated: 2026/03/25 16:22:45 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_struct_parser_data	*ft_get_parser_quad_2(int id,
		t_struct_parser_data *struct_parser)
{
	struct_parser->material_lst = ft_get_parser_material(id);
	return (struct_parser);
}

t_struct_parser_data	*ft_get_parser_quad(int id)
{
	t_list					*lst;
	t_parsing_data			d;
	t_struct_parser_data	*struct_parser;

	struct_parser = ft_malloc_id(sizeof(t_struct_parser_data), id);
	struct_parser->type = object_type_quad;
	lst = 0;
	d = (t_parsing_data){p_float, offsetof(t_quad, position.x), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float, offsetof(t_quad, position.y), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float, offsetof(t_quad, position.z), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float, offsetof(t_quad, normal.x), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float, offsetof(t_quad, normal.y), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float, offsetof(t_quad, normal.z), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float, offsetof(t_quad, size.x), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float, offsetof(t_quad, size.y), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	struct_parser->element_lst = lst;
	return (ft_get_parser_quad_2(id, struct_parser));
}

t_quad	ft_get_processed_quad(t_quad quad)
{
	t_v3f	helper;

	quad.normal = ft_v3f_normalize(quad.normal);
	if (fabsf(quad.normal.y) > 0.9f)
		helper = (t_v3f){{0.0f, 0.0f, 1.0f}};
	else
		helper = (t_v3f){{0.0f, -1.0f, 0.0f}};
	quad.u_axis = ft_v3f_normalize(ft_v3f_cross(helper, quad.normal));
	quad.v_axis = ft_v3f_cross(quad.normal, quad.u_axis);
	return (quad);
}
