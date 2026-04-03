/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:01:39 by pberne            #+#    #+#             */
/*   Updated: 2026/04/03 14:16:53 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_input_clear_just_pressed(t_data *d)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		d->input.keys[i].just_down = 0;
		d->input.keys->just_up = 0;
		i++;
	}
	i = 65535 - 256;
	while (i < 65535)
	{
		d->input.keys[i].just_down = 0;
		d->input.keys->just_up = 0;
		i++;
	}
}

void	ft_update_key_state(int keycode, int newstate, t_data *d)
{
	if (newstate == 0)
		d->input.keys[keycode].just_up = 1;
	else
		d->input.keys[keycode].just_down = 1;
	d->input.keys[keycode].isdown = newstate;
}
