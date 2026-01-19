/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:21:53 by pberne            #+#    #+#             */
/*   Updated: 2026/01/19 17:33:09 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define WIDTH_WIN 1280
# define HEIGHT_WIN 720

# define LINE_SIZE WIDTH_WIN * 4

# define IMAGE_BPP 4

# define HIDE_CURSOR 0

# define CAM_X 0.0f
# define CAM_Y 0.0f
# define CAM_Z 0.0f

/// Units / second
# define CAM_MOVEMENT_SPEED 4.0f

/// pixels per degree
# define CAM_ROTATION_SPEED 15

# define SCALING_COEF 1.0f

# define PI 3.14159265f
# define DEG2RAD 0.017453293f

# define DELTATIME_DISPLAY_DELAY 0.0f

# include "image_inlined.h"
# include "keycodes.h"
# include "libft.h"
# include "mlx.h"
# include "monitoring.h"
# include "rt_structs.h"
# include <math.h>
# include <sys/time.h>

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

void		ft_exit(int exitcode);
void		ft_exit_init(t_data *d);
int			ft_destroy(void *param);

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

void		ft_camera_init(t_data *d, t_v3f pos, t_v3f rot);
void		ft_camera_move(t_data *d);
void		ft_camera_rotate(t_data *d);
void		ft_update_rotation_data(t_data *d);
void		ft_display_camera_transform(t_data *d);

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
void		ft_draw_str(t_data *d, t_draw_arg arg, char *str);

#endif