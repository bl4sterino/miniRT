/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:56:36 by pberne            #+#    #+#             */
/*   Updated: 2026/03/23 14:31:43 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_list	*ft_get_parser_material_2(int id, t_parsing_data d, t_list *lst)
{
	d = (t_parsing_data){p_float, offsetof(t_material, color_tex), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float, offsetof(t_material, normal_tex), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	return (lst);
}

t_list	*ft_get_parser_material(int id)
{
	t_parsing_data	d;
	t_list			*lst;

	lst = 0;
	d = (t_parsing_data){p_float_0_255_to_0_1, offsetof(t_material, color.x),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float_0_255_to_0_1, offsetof(t_material, color.y),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float_0_255_to_0_1, offsetof(t_material, color.z),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float, offsetof(t_material, diffusion), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float, offsetof(t_material, reflectiveness), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float, offsetof(t_material, emission), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_float, offsetof(t_material, refraction), 0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	return (ft_get_parser_material_2(id, d, lst));
}
