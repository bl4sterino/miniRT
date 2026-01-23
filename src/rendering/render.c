/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:52:25 by pberne            #+#    #+#             */
/*   Updated: 2026/01/23 12:18:16 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void ft_print_vp(t_viewport vp)
{
	t_v3d top_right = ft_v3d_add(vp.top_left, vp.x_size);
	t_v3d bot_left = ft_v3d_add(vp.top_left, vp.y_size);
	
	double total = ft_get_triangle_area(vp.top_left, top_right, vp.bottom_right);
	total += ft_get_triangle_area(vp.top_left, vp.bottom_right, bot_left);
	printf("Area = %f\n", total);
}

void	ft_render(t_data *d)
{
	t_viewport	viewport;

	viewport = ft_get_viewport(d->scene->camera);
	ft_print_vp(viewport);


	ft_clock_start(clock_render);
	ft_basic_rt(viewport, d);
	ft_clock_set(clock_render);
}
