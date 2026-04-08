/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:21:53 by pberne            #+#    #+#             */
/*   Updated: 2026/04/08 17:07:11 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define BVH_MAX_OBJ_PER_LEAF 1
# define TASK_TILE_SIZE 16
# define TASK_LINE_SIZE 128
# define SELECTED_NONE 2147483647
# define SELECTED_SKYBOX 2147483646
# define OBJ_MOVEMENT_SPEED 20.0f
# define OBJ_ROTATION_SPEED 100.0f
# define OBJ_EXTRA_SPEED 5.0f
# define IMAGE_BPP 4
# define COL_EPSILON 0.02f

# define HIDE_CURSOR 0

# define CAM_X 0.0f
# define CAM_Y 0.0f
# define CAM_Z 0.0f

/// Units / second
# define CAM_MOVEMENT_SPEED 100
# define CAM_BOOST 5.0f

/// pixels per degree
# define CAM_ROTATION_SPEED 0.1f
# define CAM_ROTATION_SPEED_KEY 128.0f

# define DELTATIME_DISPLAY_DELAY 0.2f

# define MAX_HDR_COEF 20.0f

# define DEFAULT_STEREO_HALF_SPACE 0.5f

// Libs and struct must be included first
# include "keycodes.h"
# include "libft.h"
# include "scene_data.h"
//
# include "rt_structs.h"
# include <math.h>
# include <stdlib.h>

// mini-rt
# include "areas_inlined.h"
# include "collisions.h"
# include "colors_conversions_inlined.h"
# include "hit_side_inlined.h"
# include "image_accumulated_inlined.h"
# include "image_inlined.h"
# include "mlx.h"
# include "monitoring.h"
# include "normals_inlined.h"
# include "pixel_color_utils.h"
# include "ray_utils_inlined.h"
# include "surface_points_inlined.h"
# include "uvs.h"
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
// main

void		ft_setup_hooks(t_data *d);
void		ft_init_thread_pool(t_data *d);
void		ft_init_data(t_data *d);

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

void		ft_add_input(int keycode, t_data *d);
void		ft_add_key_range(int keycode_start, int keycode_end, t_data *d);
void		ft_update_key_state(int keycode, int newstate, t_data *d);
void		ft_input_clear_just_pressed(t_data *d);
int			ft_get_key(int keycode, t_data *d);
int			ft_get_key_down(int keycode, t_data *d);
int			ft_get_key_up(int keycode, t_data *d);
void		ft_toggle_focus(t_data *d);
void		ft_mouse_update(t_data *d);
void		ft_controls(t_data *d);

void		ft_select_objects(t_data *d);
void		ft_selected_object_controls(t_data *d);
t_v3f		ft_get_object_movement(t_data *d);
t_v3f		ft_get_object_rotation(t_data *d);
t_v3f		ft_get_object_extra(t_data *d);

void		ft_move_object(t_v3f movement, t_object *object, t_data *d,
				int *dirty_bvh);
void		ft_rotate_object(t_v3f rotation, t_object *object, t_data *d,
				int *dirty_bvh);
void		ft_extra_controls(t_v3f extra, t_object *object, t_data *d,
				int *dirty_bvh);

// camera

void		ft_camera_count(t_data *d);
void		ft_camera_move(t_data *d);
void		ft_camera_rotate(t_data *d);
void		ft_camera_zoom(t_data *d);
void		ft_render_settings(t_data *d);
void		ft_set_all_cameras_dirty(t_data *d);
void		ft_clear_dirty_cameras(t_data *d);
void		ft_prepare_cache_frame(t_data *d);

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
void		ft_draw_float(t_data *d, t_draw_arg arg, char *prefix, float nb);
void		ft_draw_float_8(t_data *d, t_draw_arg arg, char *prefix_arg,
				float nb);
void		ft_draw_str(t_data *d, t_draw_arg arg, char *str);

// rendering

void		ft_build_bvh(t_scene *scene);
t_v3f		ft_get_pixel_color(t_ray ray, t_scene *scene, t_out_buffer *out,
				int ray_target);
t_v3f		ft_get_sky_color(t_scene *scene, t_ray ray, t_out_buffer *out);

t_ray		ft_setup_ray_target(t_ray ray, t_v3f target, char bounces,
				char diffused);
t_ray		ft_setup_ray_direction(t_ray ray, t_v3f direction, char bounces,
				char diffused);
int			ft_cache_ray_target(t_data *d, t_viewport *vp,
				t_thread_render_context *c);

float		ft_shoot_ray(t_ray ray, t_scene *scene, int *hit);
float		ft_shoot_ray_smart(t_ray ray, t_scene *scene,
				t_pixel_color_context *c, int ray_target);

t_v3f		ft_shoot_ray_bvh_debug(t_ray ray, t_scene *scene);
t_v3f		ft_get_light(t_v3f position, t_v3f normal, t_scene *scene);
float		ft_shoot_ray_against_planes(t_ray ray, float max_dist,
				t_scene *scene, int *hit);
float		ft_shoot_ray_against_objects(t_ray ray, float max_dist,
				t_scene *scene, int *hit);

t_viewport	ft_get_viewport(t_camera cam, t_data *d);
void		ft_render(t_data *d);
void		*ft_thread_loop(void *arg);
t_v3f		ft_get_viewport_target(t_viewport *vp, t_thread_render_context c);
void		ft_render_mode_basic(t_data *d, t_thread_render_context *c,
				int cam_idx);
void		ft_render_mode_stereo(t_data *d, t_thread_render_context *c,
				int cam_idx, t_ray ray);
void		ft_post_process(t_data *d);

// utils
t_data		*ft_get_data(void);
void		ft_set_data(t_data *d);
t_v3f		ft_cam_v3f_to_euler(t_v3f cam_direction);
t_v3f		ft_cam_euler_to_v3f(t_v3f euler);
float		ft_get_triangle_area(t_v3f A, t_v3f B, t_v3f C);
int			rect_contains(t_rect rect, t_v2i pos);

t_camera	*get_active_camera(t_scene *s);
void		add_camera(t_scene *scene, t_camera *cam);
void		remove_camera(t_scene *scene);
void		refresh_grid(t_data *d);
void		recompute_grid(t_scene *scene, t_rect rect);

// debug

void		ft_debug_gc(t_data *d);

#endif
