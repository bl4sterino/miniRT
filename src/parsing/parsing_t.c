/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:33:23 by pberne            #+#    #+#             */
/*   Updated: 2026/02/19 15:05:28 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_triangle	ft_get_processed_triangle(t_triangle tri)
{
	t_v3d	center;
	t_v3d	ab;
	t_v3d	ac;

	center = ft_v3d_add(tri.points.a, tri.points.b);
	center = ft_v3d_add(center, tri.points.c);
	tri.position = ft_v3d_scale(center, 1.0 / 3.0);
	ab = ft_v3d_sub(tri.points.b, tri.points.a);
	ac = ft_v3d_sub(tri.points.c, tri.points.a);
	tri.normal = ft_v3d_normalize(ft_v3d_cross(ac, ab));
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
		d = (t_parsing_data){p_double, offsetof(t_triangle, points.p[i].x), 0};
		ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
		d = (t_parsing_data){p_double, offsetof(t_triangle, points.p[i].y), 0};
		ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
		d = (t_parsing_data){p_double, offsetof(t_triangle, points.p[i].z), 0};
		ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
		i++;
	}
	struct_parser->element_lst = lst;
	return (ft_get_parser_triangle_2(id, struct_parser));
}
