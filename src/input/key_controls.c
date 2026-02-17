/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:48:05 by pberne            #+#    #+#             */
/*   Updated: 2026/02/17 13:46:01 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"



void	ft_controls(t_data *d)
{
	ft_debug_gc(d);
	if (ft_get_key_down(KEY_E, d))
	{
		d->render_mode = !d->render_mode;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(MOUSE_SCROLL_DOWN, d))
	{
		d->scene->camera.fov *= 1.05;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(MOUSE_SCROLL_UP, d))
	{
		d->scene->camera.fov *= 0.95;
		d->dirty_frame = 1;
	}
	ft_select_objects(d);
	if (d->selected_object != SELECTED_NONE || d->selected_light != -1)
		ft_selected_object_controls(d);
		
}
