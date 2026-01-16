/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:36:28 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 13:54:57 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

# define KEY_ESCAPE 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101
# define KEY_SPACE 32
# define KEY_CTRL_L 65507
# define KEY_ALT 65513
# define KEY_KP_PLUS 65451
# define KEY_KP_MINUS 65453

#define KEY_KP_0 65438
#define KEY_KP_1 65436
#define KEY_KP_2 65433
#define KEY_KP_3 65435
#define KEY_KP_4 65430
#define KEY_KP_5 65437
#define KEY_KP_6 65432
#define KEY_KP_7 65429
#define KEY_KP_8 65431
#define KEY_KP_9 65434

# define MOUSE_LEFT 1
# define MOUSE_MIDDLE 2
# define MOUSE_RIGHT 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# include "libft.h"

typedef struct s_key_list
{
	struct s_key_list	*next;
	int					keycode;
	int					isdown;
	int					just_down;
	int					just_up;
}						t_key_list;

typedef struct s_input
{
	t_v2i				mouse_pos;
	t_v2i				mouse_pos_previous;
	t_v2i				mouse_delta;
	unsigned long		mouse_reset;
	int					focus;
	t_key_list			*keys;
}						t_input;

#endif