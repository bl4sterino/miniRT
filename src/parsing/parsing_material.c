/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:56:36 by pberne            #+#    #+#             */
/*   Updated: 2026/02/20 13:36:45 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_list *ft_get_parser_material(int id)
{
	t_parsing_data	d;
	t_list			*lst;

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
	d = (t_parsing_data){p_double_try_or_0, offsetof(t_material, diffusion),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	d = (t_parsing_data){p_double_try_or_0, offsetof(t_material, reflectiveness),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
		d = (t_parsing_data){p_double_try_or_0, offsetof(t_material, emission),
		0};
	ft_lstadd_back(&lst, ft_lstnew_gc_id(ft_get_pdata(id, d), id));
	return (lst);
}
