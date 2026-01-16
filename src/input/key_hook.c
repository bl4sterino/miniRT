/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:26:37 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 10:30:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	ft_key_down(int keycode, t_data *d)
{
	ft_update_key_state(keycode, 1, d);
	return (0);
}

int	ft_key_up(int keycode, t_data *d)
{
	ft_update_key_state(keycode, 0, d);
	return (0);
}

int	ft_mouse_down(int button, int x, int y, t_data *d)
{
	ft_update_key_state(button, 1, d);
	d->input.mouse_pos.x = x;
	d->input.mouse_pos.y = y;
	return (0);
}

int	ft_mouse_up(int button, int x, int y, t_data *d)
{
	ft_update_key_state(button, 0, d);
	d->input.mouse_pos.x = x;
	d->input.mouse_pos.y = y;
	return (0);
}
