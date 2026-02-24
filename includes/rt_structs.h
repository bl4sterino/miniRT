/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:04:26 by pberne            #+#    #+#             */
/*   Updated: 2026/02/24 10:10:01 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H

# include "rt.h"

enum					e_dimensions
{
	WIDTH_WIN = 1280,
	HEIGHT_WIN = 720,
	LINE_SIZE = WIDTH_WIN * 4,
	SCREEN_SIZE = WIDTH_WIN * HEIGHT_WIN
};

typedef enum e_render_mode
{
	DEFAULT,
	DEBUG
}						t_render_mode;

typedef struct s_rgb
{
	char				r;
	char				g;
	char				b;
}						t_rgb;

typedef struct s_image
{
	void				*ptr;
	char				*addr;
	double				*accumulated_addr;
	double				*averaged_colors;
	int					bpp;
	int					line_size;
	int					endian;
}						t_image;

typedef struct s_rotation_data
{
	float				yaw;
	float				pitch;
	float				cos_y;
	float				sin_y;
	float				cos_p;
	float				sin_p;
}						t_rotation_data;

typedef struct s_render_task
{
	int					y_start;
	int					y_end;
	int					x_start;
	int					x_end;
	int					line_end;
}						t_render_task;

typedef struct s_threads_data
{
	int					count;
	pthread_t			*threads;
	int					tasks_count;
	int					tasks_total_count;
	int					finished_tasks;
	t_render_task		*tasks;
	pthread_mutex_t		task_mutex;
	pthread_cond_t		task_cond;
	pthread_cond_t		done_cond;
	int					run_threads;
}						t_threads_data;

typedef struct s_opencl_data
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_program			program;
	cl_kernel			kernel_average;
	cl_kernel			kernel_blur;
	cl_command_queue	command_queue;

	cl_mem				accumulated_buff;
	cl_mem				a;
	cl_mem				b;
}						t_opencl_data;

typedef struct s_viewport
{
	t_v3d				u;
	t_v3d				v;
	t_v3d				x_delta;
	t_v3d				y_delta;
	t_v3d				top_left;
	t_v3d				top_right;
	t_v3d				bottom_left;
	t_v3d				bottom_right;

}						t_viewport;

typedef struct t_data
{
	void				*mlx;
	void				*window;
	t_image				image;
	t_input				input;
	double				deltatime;
	struct timeval		last_tv;
	char				*fpsstr;
	double				frame_count;
	char				dirty_frame;
	char				ray_bounces;
	int					target_ray_bounces;
	t_scene				*scene;
	t_viewport			viewport;
	t_threads_data		threads_data;
	t_render_mode		render_mode;
	int					selected_object;
	int					selected_light;
	t_opencl_data		opencl;
}						t_data;

typedef struct s_ray
{
	t_v3d				origin;
	t_v3d				direction;
	t_v3d				inv_dir;
	int					inv_sign[3];
	char				remaining_bounces;
}						t_ray;

typedef struct s_ray_result
{
	int					id;
	t_v3d				normal;
}						t_ray_result;

typedef struct s_bvh_context
{
	int					stack[64];
	int					stack_ptr;
	double				t;
	double				best_dist;
	int					best_index;
	t_bvh_node			*current;
}						t_bvh_context;

typedef struct s_bvh_context_debug
{
	int					stack[64];
	int					stack_ptr;
	int					nodes_traversed;
	double				t;
	double				best_dist;
	int					best_index;
	t_bvh_node			*current;
}						t_bvh_context_debug;

typedef struct s_thread_render_context
{
	t_v2i				pixel;
	t_ray				ray;
	t_v3d				target;
	t_v3d				y_target;
}						t_thread_render_context;

typedef struct s_get_light_context
{
	int					i;
	t_ray				light_ray;
	double				light_dist;
	double				dist;
	int					hit;
	t_v3d				color;
	t_v3d				new_color;
	double				plane_dist;
}						t_get_light_context;

typedef struct s_pixel_color_context
{
	int					hit;
	double				distance;
	t_v3d				out_color;
	t_v3d				hit_normal;
	t_v3d				hit_point;
	t_v3d				light_color;
	t_v3d				reflection_color;
	t_material			mat;
	double				do_reflect;
	t_v3d				reflected;
	t_v3d				new_dir;

}						t_pixel_color_context;

typedef struct s_viewport_context
{
	t_camera			cam;
	double				aspect_ratio;
	double				theta;
	double				half_width;
	double				half_height;
	t_v3d				cam_right;
	t_v3d				cam_up;
	t_v3d				pixel_center_offset;
}						t_viewport_context;

#endif