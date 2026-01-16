/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:01:39 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 10:30:45 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_add_input(int keycode, t_data *d)
{
	t_key_list	*key;

	key = ft_malloc(sizeof(t_key_list));
	if (!key)
		ft_exit(MALLOC_FAILED);
	key->keycode = keycode;
	key->isdown = 0;
	key->just_down = 0;
	key->just_up = 0;
	key->next = d->input.keys;
	d->input.keys = key;
}

void	ft_input_init2(t_data *d)
{
	ft_add_input(KEY_KP_0, d);
	ft_add_input(KEY_KP_1, d);
	ft_add_input(KEY_KP_2, d);
	ft_add_input(KEY_KP_3, d);
	ft_add_input(KEY_KP_4, d);
	ft_add_input(KEY_KP_5, d);
	ft_add_input(KEY_KP_6, d);
	ft_add_input(KEY_KP_7, d);
	ft_add_input(KEY_KP_8, d);
	ft_add_input(KEY_KP_9, d);
}

void	ft_input_init(t_data *d)
{
	d->input.focus = 0;
	d->input.keys = 0;
	d->input.mouse_pos.x = 0;
	d->input.mouse_pos.y = 0;
	d->input.mouse_pos_previous.x = 0;
	d->input.mouse_pos_previous.y = 0;
	ft_add_input(KEY_ESCAPE, d);
	ft_add_input(KEY_SPACE, d);
	ft_add_input(KEY_CTRL_L, d);
	ft_add_input(KEY_ALT, d);
	ft_add_input(KEY_KP_PLUS, d);
	ft_add_input(KEY_KP_MINUS, d);
	ft_add_input(MOUSE_MIDDLE, d);
	ft_add_input(MOUSE_SCROLL_UP, d);
	ft_add_input(MOUSE_SCROLL_DOWN, d);
	ft_add_input(MOUSE_LEFT, d);
	ft_add_input(MOUSE_RIGHT, d);
	ft_add_input(KEY_Q, d);
	ft_add_input(KEY_E, d);
	ft_add_input(KEY_W, d);
	ft_add_input(KEY_A, d);
	ft_add_input(KEY_S, d);
	ft_add_input(KEY_D, d);
	ft_input_init2(d);
}

void	ft_input_clear_just_pressed(t_data *d)
{
	t_key_list	*key;

	key = d->input.keys;
	while (key)
	{
		key->just_down = 0;
		key->just_up = 0;
		key = key->next;
	}
}

void	ft_update_key_state(int keycode, int newstate, t_data *d)
{
	t_key_list	*key;

	key = d->input.keys;
	while (key)
	{
		if (key->keycode == keycode)
		{
			if (newstate == 0)
				key->just_up = 1;
			else
				key->just_down = 1;
			key->isdown = newstate;
			return ;
		}
		key = key->next;
	}
}
