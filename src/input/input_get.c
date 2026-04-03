/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:40:14 by pberne            #+#    #+#             */
/*   Updated: 2026/04/03 11:53:08 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/// @brief Returns true if the key is being pressed
int	ft_get_key(int keycode, t_data *d)
{
	if (keycode < 0 || keycode > 0xFFFF)
		return (0);
	return (d->input.keys[keycode].isdown);
}

/// @brief Returns true if the key has been pressed during this frame
int	ft_get_key_down(int keycode, t_data *d)
{
	if (keycode < 0 || keycode > 0xFFFF)
		return (0);
	return (d->input.keys[keycode].just_down);
}

/// @brief Returns true if the key has been released this frame
int	ft_get_key_up(int keycode, t_data *d)
{
	if (keycode < 0 || keycode > 0xFFFF)
		return (0);
	return (d->input.keys[keycode].just_up);
}
