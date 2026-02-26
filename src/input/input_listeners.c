/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:10:20 by pberne            #+#    #+#             */
/*   Updated: 2026/02/26 10:31:11 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void ft_input_init_2(t_data *d)
{
	ft_add_input(KEY_W, d);
	ft_add_input(KEY_A, d);
	ft_add_input(KEY_S, d);
	ft_add_input(KEY_D, d);
	ft_add_input(KEY_F, d);
	ft_add_input(KEY_G, d);
	ft_add_input(KEY_R, d);
	ft_add_input(KEY_B, d);
	ft_add_input(KEY_N, d); 	
}

void	ft_input_init(t_data *d)
{
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
	ft_add_key_range(KEY_KP_7, KEY_KP_0, d);
	ft_add_key_range(KEY_F1, KEY_F12, d);
	ft_add_key_range(KEY_LEFT, KEY_DOWN, d);
	ft_add_input(KEY_PGUP, d);
	ft_add_input(KEY_PGDN, d);
	ft_add_input(KEY_KP_DOT, d);
	ft_add_input(KEY_KP_DIV, d);
	ft_add_input(KEY_KP_MULT, d);
	ft_input_init_2(d);
}
