/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_gc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:15:08 by pberne            #+#    #+#             */
/*   Updated: 2026/01/24 07:19:15 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_debug_gc(t_data *d)
{
	if (ft_get_key_down(KEY_F1, d))
		ft_gc_print_count_id(1);
	if (ft_get_key_down(KEY_F2, d))
		ft_gc_print_count_id(2);
	if (ft_get_key_down(KEY_F3, d))
		ft_gc_print_count_id(3);
	if (ft_get_key_down(KEY_F4, d))
		ft_gc_print_count_id(4);
	if (ft_get_key_down(KEY_F12, d))
		ft_gc_print_count();
}
