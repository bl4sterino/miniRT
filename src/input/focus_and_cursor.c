/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   focus_and_cursor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:31:27 by pberne            #+#    #+#             */
/*   Updated: 2026/04/03 14:11:06 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_toggle_focus(t_data *d)
{
	d->input.focus = !d->input.focus;
	if (d->input.focus)
	{
		if (HIDE_CURSOR)
			mlx_mouse_hide(d->mlx, d->window);
		mlx_mouse_move(d->mlx, d->window, WIDTH_WIN / 2, HEIGHT_WIN / 2);
		d->input.mouse_pos.x = WIDTH_WIN / 2;
		d->input.mouse_pos.y = WIDTH_WIN / 2;
		d->input.mouse_pos_previous.x = d->input.mouse_pos.x;
		d->input.mouse_pos_previous.y = d->input.mouse_pos.y;
		d->input.mouse_delta.x = 0;
		d->input.mouse_delta.y = 0;
	}
	else
	{
		if (HIDE_CURSOR)
			mlx_mouse_show(d->mlx, d->window);
	}
}

void	ft_recenter_mouse(t_data *d)
{
	int	useless_pointer;

	if ((d->input.mouse_pos.x < WIDTH_WIN / 4
			|| d->input.mouse_pos.x > WIDTH_WIN * 0.75f)
		|| (d->input.mouse_pos.y < HEIGHT_WIN / 4
			|| d->input.mouse_pos.y > HEIGHT_WIN * 0.75f))
	{
		mlx_mouse_move(d->mlx, d->window, WIDTH_WIN / 2, HEIGHT_WIN / 2);
		mlx_mouse_get_pos(d->mlx, d->window, &useless_pointer,
			&useless_pointer);
		d->input.mouse_pos.x = WIDTH_WIN / 2;
		d->input.mouse_pos.y = HEIGHT_WIN / 2;
	}
}

void	ft_mouse_update(t_data *d)
{
	mlx_mouse_get_pos(d->mlx, d->window, &(d->input.mouse_pos.x),
		&(d->input.mouse_pos.y));
	if (ft_get_key_down(XK_Alt_L, d))
		ft_toggle_focus(d);
	if (d->input.focus)
	{
		d->input.mouse_delta.x = d->input.mouse_pos.x
			- d->input.mouse_pos_previous.x;
		d->input.mouse_delta.y = d->input.mouse_pos.y
			- d->input.mouse_pos_previous.y;
		ft_recenter_mouse(d);
	}
	else
	{
		d->input.mouse_delta.x = 0;
		d->input.mouse_delta.y = 0;
	}
}
