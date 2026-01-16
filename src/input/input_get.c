/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:40:14 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 14:03:17 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
