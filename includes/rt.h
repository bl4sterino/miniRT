/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:21:53 by pberne            #+#    #+#             */
/*   Updated: 2026/01/31 18:10:31 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define DISPLAY_BVH 1
# define BVH_MAX_OBJ_PER_LEAF 1
# define TILE_SIZE 16
# define RAY_BOUNCES 1

# define IMAGE_BPP 4

# define HIDE_CURSOR 0

# define CAM_X 0.0f
# define CAM_Y 0.0f
# define CAM_Z 0.0f

/// Units / second
# define CAM_MOVEMENT_SPEED 150

/// pixels per degree
# define CAM_ROTATION_SPEED 0.1

# define DELTATIME_DISPLAY_DELAY 0.0f

// Libs and struct must be included first
# include "keycodes.h"
# include "libft.h"
# include "scene_data.h"
//
# include "rt_structs.h"
# include <math.h>
# include <stdlib.h>

// mini-rt
# include "collisions_inlined.h"
# include "image_accumulated_inlined.h"
# include "image_inlined.h"
# include "mlx.h"
# include "monitoring.h"
# include "normals_inlined.h"
# include "ray_utils_inlined.h"
# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>

typedef enum e_malloc_id
{
	malloc_id_default,
	malloc_id_parsing,
	malloc_id_scene,
	malloc_id_frame
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
void		ft_exit_destroy_task_mutex(void *d);
void		ft_exit_destroy_task_cond(void *d);
void		ft_exit_destroy_done_cond(void *d);
void		ft_exit_thread_cancel(void *d);

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

void		ft_build_bvh(t_scene *scene);
t_v3d		ft_get_pixel_color(t_ray ray, t_scene *scene);

t_ray		ft_setup_ray_target(t_ray ray, t_v3d target, char bounces);
t_ray		ft_setup_ray_direction(t_ray ray, t_v3d direction, char bounces);

double		ft_shoot_ray(t_ray ray, t_scene *scene, int *hit);

t_v3d		ft_shoot_ray_bvh_debug(t_ray ray, t_scene *scene);
t_v3d		ft_get_light(t_v3d position, t_v3d normal, t_scene *scene);
double		ft_shoot_ray_against_planes(t_ray ray, double max_dist,
				t_scene *scene, int *hit);
double		ft_shoot_ray_against_objects(t_ray ray, double max_dist,
				t_scene *scene, int *hit);

t_viewport	ft_get_viewport(t_camera cam);
void		ft_setup_tasks(t_data *d);

void		ft_setup_tasks(t_data *d);
void		*ft_thread_loop(void *arg);

void		ft_push_accumulated_data_to_image(t_data *d);

// utils

t_v3d		ft_cam_v3d_to_euler(t_v3d cam_direction);
t_v3d		ft_cam_euler_to_v3d(t_v3d euler);
double		ft_get_triangle_area(t_v3d A, t_v3d B, t_v3d C);

// debug

void		ft_debug_gc(t_data *d);

#endif