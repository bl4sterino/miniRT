/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:21:53 by pberne            #+#    #+#             */
/*   Updated: 2026/01/23 09:31:53 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define IMAGE_BPP 4

# define HIDE_CURSOR 0

# define CAM_X 0.0f
# define CAM_Y 0.0f
# define CAM_Z 0.0f

/// Units / second
# define CAM_MOVEMENT_SPEED 4.0f

/// pixels per degree
# define CAM_ROTATION_SPEED 50

# define PI 3.14159265358979323846

# define DEG2RAD 0.01745329251

# define DELTATIME_DISPLAY_DELAY 0.0f

// Libs and struct must be included first
# include "keycodes.h"
# include "libft.h"
# include "scene_data.h"
//
# include "rt_structs.h"
# include <math.h>

// mini-rt
# include "image_inlined.h"
# include "mlx.h"
# include "monitoring.h"
# include "ray_utils_inlined.h"
# include <stddef.h>
# include <sys/time.h>

typedef enum e_malloc_id
{
	malloc_id_default,
	malloc_id_parsing
}			t_malloc_id;

// hooks

int			ft_key_down(int keycode, t_data *d);
int			ft_key_up(int keycode, t_data *d);
int			ft_mouse_down(int button, int x, int y, t_data *d);
int			ft_mouse_up(int button, int x, int y, t_data *d);
int			ft_mouse_move(int x, int y, t_data *d);

// update loop

int			ft_exec_updates(t_data *d);
void		ft_early_update(t_data *d);
void		ft_late_update(t_data *d);
int			ft_update_time(t_data *d);

// exit

int			ft_exit_hook(void *param);
void		ft_exit_destroy_image(void *d);
void		ft_exit_destroy_window(void *d);
void		ft_exit_destroy_display(void *d);
void		ft_exit_autorepeaton(void *d);

// input

void		ft_input_init(t_data *d);
void		ft_update_key_state(int keycode, int newstate, t_data *d);
void		ft_input_clear_just_pressed(t_data *d);
int			ft_get_key(int keycode, t_data *d);
int			ft_get_key_down(int keycode, t_data *d);
int			ft_get_key_up(int keycode, t_data *d);
void		ft_toggle_focus(t_data *d);
void		ft_mouse_update(t_data *d);
void		ft_controls(t_data *d);

// camera

void		ft_camera_move(t_data *d);
void		ft_camera_rotate(t_data *d);

// time

int			ft_update_time(t_data *d);
double		ft_get_real_time(void);

// ui

typedef struct s_draw_arg
{
	t_v2i	pos;
	t_v2i	size;
	t_rgb	background_color;
}			t_draw_arg;

void		ft_hud_display(t_data *d);

void		ft_draw_int(t_data *d, t_draw_arg arg, char *prefix, int nb);
void		ft_draw_double(t_data *d, t_draw_arg arg, char *prefix, double nb);
void		ft_draw_double_8(t_data *d, t_draw_arg arg, char *prefix_arg,
				double nb);
void		ft_draw_str(t_data *d, t_draw_arg arg, char *str);

// rendering

t_viewport	ft_get_viewport(t_camera cam);
void		ft_render(t_data *d);

// utils

t_v3d		ft_cam_v3d_to_euler(t_v3d cam_direction);
t_v3d		ft_cam_euler_to_v3d(t_v3d euler);

#endif