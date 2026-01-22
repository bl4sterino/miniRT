/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:40:14 by pberne            #+#    #+#             */
/*   Updated: 2026/01/22 10:11:37 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/// @brief Returns true if the key is being pressed
int	ft_get_key(int keycode, t_data *d)
{
	t_key_list	*key;

	key = d->input.keys;
	while (key)
	{
		if (key->keycode == keycode)
			return (key->isdown);
		key = key->next;
	}
	return (0);
}

/// @brief Returns true if the key has been pressed during this frame
int	ft_get_key_down(int keycode, t_data *d)
{
	t_key_list	*key;

	key = d->input.keys;
	while (key)
	{
		if (key->keycode == keycode)
			return (key->just_down);
		key = key->next;
	}
	return (0);
}

/// @brief Returns true if the key has been released this frame
int	ft_get_key_up(int keycode, t_data *d)
{
	t_key_list	*key;

	key = d->input.keys;
	while (key)
	{
		if (key->keycode == keycode)
			return (key->just_up);
		key = key->next;
	}
	return (0);
}
