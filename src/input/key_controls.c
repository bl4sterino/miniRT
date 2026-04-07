/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:48:05 by pberne            #+#    #+#             */
/*   Updated: 2026/04/07 16:12:30 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_controls(t_data *d)
{
	ft_debug_gc(d);
	ft_camera_move(d);
	ft_camera_rotate(d);
	ft_camera_zoom(d);
	ft_camera_count(d);
	ft_render_settings(d);
	ft_select_objects(d);
	if (d->selected_object != SELECTED_NONE || d->selected_light != -1)
		ft_selected_object_controls(d);
}
