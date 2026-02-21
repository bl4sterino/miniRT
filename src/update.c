/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:43:31 by pberne            #+#    #+#             */
/*   Updated: 2026/02/21 16:12:46 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_update(t_data *d)
{
	ft_controls(d);
	d->viewport = ft_get_viewport(d->scene->camera, d);
}

void	ft_early_update(t_data *d)
{
	ft_update_time(d);
	if (ft_get_key_down(KEY_ESCAPE, d))
		ft_exit(EXIT_SUCCESS);
	ft_mouse_update(d);
}

void	ft_late_update(t_data *d)
{
	ft_input_clear_just_pressed(d);
	d->input.mouse_pos_previous.x = d->input.mouse_pos.x;
	d->input.mouse_pos_previous.y = d->input.mouse_pos.y;
}

/// used to draw things directly on screen to prevent them
/// to be overwritten by mlx_put_image_to_window
void	ft_post_render(t_data *d)
{
	ft_hud_display(d);
}

int	ft_exec_updates(t_data *d)
{
	ft_clock_clear();
	ft_clock_start(clock_frame);
	ft_early_update(d);
	ft_update(d);
	ft_late_update(d);
	ft_setup_tasks(d);
	ft_push_accumulated_data_to_image(d);
	mlx_put_image_to_window(d->mlx, d->window, d->image.ptr, 0, 0);
	ft_clock_set(clock_frame);
	ft_post_render(d);
	return (0);
}
