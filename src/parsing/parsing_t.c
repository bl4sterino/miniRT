/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:33:23 by pberne            #+#    #+#             */
/*   Updated: 2026/04/10 20:48:11 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_triangle	ft_get_processed_triangle(t_triangle tri)
{
	t_v3f	center;
	t_v3f	ab;
	t_v3f	ac;

	center = ft_v3f_add(tri.points[0], tri.points[1]);
	center = ft_v3f_add(center, tri.points[2]);
	tri.position = ft_v3f_scale(center, 1.0f / 3.0f);
	ab = ft_v3f_sub(tri.points[1], tri.points[0]);
	ac = ft_v3f_sub(tri.points[2], tri.points[0]);
	tri.normal = ft_v3f_normalize(ft_v3f_cross(ac, ab));
	if (tri.normals[0].x == 0.0 && tri.normals[0].y == 0.0
		&& tri.normals[0].z == 0.0 && tri.normals[1].x == 0.0
		&& tri.normals[1].y == 0.0 && tri.normals[1].z == 0.0
		&& tri.normals[2].x == 0.0 && tri.normals[2].y == 0.0
		&& tri.normals[2].z == 0.0)
	{
		tri.normals[0] = tri.normal;
		tri.normals[1] = tri.normal;
		tri.normals[2] = tri.normal;
	}
	return (tri);
}

t_struct_parser_data	*ft_get_parser_triangle_2(int id,
		t_struct_parser_data *struct_parser)
{
	struct_parser->material_lst = ft_get_parser_material(id);
	return (struct_parser);
}

t_struct_parser_data	*ft_get_parser_triangle(int id)
{
	t_list					*lst;
	t_parsing_data			d;
	t_struct_parser_data	*struct_parser;
	int						i;

	struct_parser = ft_malloc_id(sizeof(t_struct_parser_data), id);
	struct_parser->type = object_type_triangle;
	lst = 0;
	i = 0;
	while (i < 3)
	{
		d = (t_parsing_data){p_float, offsetof(t_triangle, points[i].x), 0};
		ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
		d = (t_parsing_data){p_float, offsetof(t_triangle, points[i].y), 0};
		ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
		d = (t_parsing_data){p_float, offsetof(t_triangle, points[i].z), 0};
		ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
		i++;
	}
	struct_parser->element_lst = lst;
	return (ft_get_parser_triangle_2(id, struct_parser));
}
