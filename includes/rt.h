/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:21:53 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 11:39:14 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define WIDTH_WIN 1920
# define HEIGHT_WIN 1080

# define CULLING_OFFSET 50
# define X_WIN_MIN -CULLING_OFFSET
# define X_WIN_MAX WIDTH_WIN + CULLING_OFFSET
# define Y_WIN_MIN -CULLING_OFFSET
# define Y_WIN_MAX HEIGHT_WIN + CULLING_OFFSET
# define IMAGE_BPP 4

# define MALLOC_FAILED 2
# define OPEN_FAIL 3
# define HIDE_CURSOR 0

# define CAM_X 0.0f
# define CAM_Y 0.0f
# define CAM_Z 0.0f

/// Units / second
# define CAM_MOVEMENT_SPEED 4.0f
/// pixels per degree
# define CAM_ROTATION_SPEED 15

# define PI 3.14159265f
# define DEG2RAD 0.017453293f

# define DELTATIME_DISPLAY_DELAY 0.0f

# include "keycodes.h"
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <sys/time.h>

typedef struct s_image
{
	void			*ptr;
	char			*addr;
	float			*depth_map;
	int				bpp;
	int				line_size;
	int				endian;
}					t_image;

typedef struct s_transform
{
	t_v3f			pos;
	t_v3f			rot;
}					t_transform;

typedef struct s_rotation_data
{
	float			yaw;
	float			pitch;
	float			cosY;
	float			sinY;
	float			cosP;
	float			sinP;
}					t_rotation_data;

typedef struct s_camera
{
	t_transform		t;
	float			speed;
	float			fov;
	float			focal;
	float			iso_scale;
	t_rotation_data	rot_d;
}					t_camera;

typedef struct s_point
{
	t_v3f			pos;
	t_rgb			color;
}					t_point;

// Parsing

typedef struct s_screenpoint
{
	int				x;
	int				y;
	float			depth;
	t_rgb			color;
}					t_screenpoint;

typedef struct s_map_data
{
	t_v2i			size;
	int				point_count;
	t_point			*points;
	t_point			*rotated_points;
	t_screenpoint	*screen_points;
	t_v3f			map_rotation;
	int				*edges;
	int				edge_pairs;
	int				flag_for_rebake;
}					t_map_data;

typedef struct t_data
{
	t_map_data		map;
	void			*mlx;
	void			*window;
	t_image			image;
	t_input			input;
	double			deltatime;
	struct timeval	last_tv;
	char			*fpsstr;
	t_camera		cam;
	int				projection;

	unsigned long	frame_count;
}					t_data;

typedef struct s_parsing_data
{
	char			*line;
	int				i;
	int				fd;
	t_list			*lst;
}					t_parsing_data;

typedef struct s_line_data
{
	float			depth_step;
	t_v3f			color_step;
	t_v2i			delta;
	t_v2i			sign;
}					t_line_data;

typedef struct s_obj_parsing_data
{
	int				vert_count;
	t_list			*vert_list;
	int				tri_count;
	t_list			*tri_list;
}					t_obj_parsing_data;

// parsing

void				ft_parse_map(char *filepath, t_data *d);
void				ft_parse_fdf_map(char *filepath, t_data *d, t_v2i size,
						t_v2i pos);
void				ft_print_map(t_data *d);
void				ft_create_edges_fdf(t_data *d, t_v3i v);
void				ft_offset_fdf_to_center(t_data *d);
void				ft_create_edges_obj(t_data *d, int fd);
void				ft_parse_obj_map(char *filepath, t_data *d);
void				ft_skip_float(char *str, int *i);
void				ft_init_var_and_capitalize(char *str, int *i, int *x);
void				ft_update_size_x(t_v2i *size, t_v2i pos);
int					ft_add_triangle(char *str, t_list **triangle_list);
void				ft_add_triangles_clean(t_data *d, t_list *triangle_list);
void				ft_push_edges_to_array(t_data *d, t_list **edge_array,
						int edge_count);

// hooks

int					ft_key_down(int keycode, t_data *d);
int					ft_key_up(int keycode, t_data *d);
int					ft_mouse_down(int button, int x, int y, t_data *d);
int					ft_mouse_up(int button, int x, int y, t_data *d);
int					ft_mouse_move(int x, int y, t_data *d);

// update loop

int					ft_exec_updates(t_data *d);
void				ft_early_update(t_data *d);
void				ft_late_update(t_data *d);
int					ft_update_time(t_data *d);

// ft_image.c

void				ft_put_pxl_d(t_image *img, t_v2i pos, int color,
						float depth);
void				ft_put_pxl(t_image *img, t_v2i pos, int color);
void				ft_create_image(t_data *d);
int					ft_rgb_to_int(t_rgb color);
void				ft_draw_rectangle(t_image image, t_v2i pos, t_v2i size,
						t_rgb color);
t_rgb				ft_int_to_rgb(int color);
int					ft_uc_color_to_int(unsigned char r, unsigned char g,
						unsigned char b);
int					ft_color_lerp(int color1, int color2, float t);
int					ft_color_lerp_rgb_to_int(t_rgb c1, t_rgb c2, float t);

// exit

void				ft_exit(int exitcode);
void				ft_exit_init(t_data *d);
int					ft_destroy(void *param);

// input

void				ft_input_init(t_data *d);
void				ft_update_key_state(int keycode, int newstate, t_data *d);
void				ft_input_clear_just_pressed(t_data *d);
int					ft_get_key(int keycode, t_data *d);
int					ft_get_key_down(int keycode, t_data *d);
int					ft_get_key_up(int keycode, t_data *d);
void				ft_toggle_focus(t_data *d);
void				ft_mouse_update(t_data *d);
void				ft_controls(t_data *d);

// camera

void				ft_camera_init(t_data *d);
void				ft_camera_move(t_data *d);
void				ft_camera_rotate(t_data *d);
void				ft_update_rotation_data(t_data *d);
void				ft_display_camera_transform(t_data *d);

// ui

typedef struct s_draw_arg
{
	t_v2i			pos;
	t_v2i			size;
	t_rgb			background_color;
}					t_draw_arg;

void				ft_draw_int(t_data *d, t_draw_arg arg, char *prefix,
						int nb);
void				ft_draw_double(t_data *d, t_draw_arg arg, char *prefix,
						double nb);
void				ft_draw_str(t_data *d, t_draw_arg arg, char *str);

#endif