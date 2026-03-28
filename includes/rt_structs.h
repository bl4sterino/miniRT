/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:04:26 by pberne            #+#    #+#             */
/*   Updated: 2026/03/28 19:06:50 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H

# include "rt.h"
# include <immintrin.h>

enum				e_dimensions
{
	WIDTH_WIN = 1280,
	HEIGHT_WIN = 720,
	LINE_SIZE = WIDTH_WIN * 4,
	SCREEN_SIZE = WIDTH_WIN * HEIGHT_WIN,
	WINDOW_SIZE = SCREEN_SIZE
};

enum				e_task_mode
{
	TASK_MODE_UNSET,
	TASK_MODE_TILE,
	TASK_MODE_LINE
};

typedef enum e_render_mode
{
	RENDER_DEFAULT,
	RENDER_BVH,
	RENDER_NORMALS,
	RENDER_DEPTH
}					t_render_mode;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb;

typedef struct s_image
{
	void			*ptr;
	char			*addr;
	t_v3f			*current_frame;
	t_v3f			*averaged_colors;
	t_v3f			*normals;
	t_v3f			*positions;
	int				bpp;
	int				line_size;
	int				endian;
}					t_image;

typedef struct s_rotation_data
{
	float			yaw;
	float			pitch;
	float			cos_y;
	float			sin_y;
	float			cos_p;
	float			sin_p;
}					t_rotation_data;

typedef struct s_render_task
{
	int				y_start;
	int				y_end;
	int				x_start;
	int				x_end;
	int				line_end;
}					t_render_task;

typedef struct s_threads_data
{
	int				count;
	int				task_mode;
	pthread_t		*threads;
	int				tasks_count;
	int				tasks_total_count;
	int				finished_tasks;
	t_render_task	*tasks;
	pthread_mutex_t	task_mutex;
	pthread_cond_t	task_cond;
	pthread_cond_t	done_cond;
	int				run_threads;
}					t_threads_data;

typedef struct s_viewport
{
	t_v3f			u;
	t_v3f			v;
	t_v3f			x_delta;
	t_v3f			y_delta;
	t_v3f			top_left;
	t_v3f			top_right;
	t_v3f			bottom_left;
	t_v3f			bottom_right;

}					t_viewport;

typedef struct s_data
{
	void			*mlx;
	void			*window;
	t_image			image;
	t_input			input;
	double			deltatime;
	double			total_time;
	double			total_frames;
	struct timeval	last_tv;
	char			*fpsstr;
	float			frame_count;
	char			dirty_frame;
	char			ray_bounces;
	int				target_ray_bounces;
	t_scene			*scene;
	t_viewport		viewport;
	t_threads_data	threads_data;
	t_render_mode	render_mode;
	int				selected_object;
	int				selected_light;
}					t_data;

typedef struct s_ray
{
	t_v3f			origin;
	t_v3f			direction;
	t_v3f			inv_dir;
	int				inv_sign[3];
	char			remaining_bounces;
}					t_ray;

typedef struct s_ray_result
{
	int				id;
	t_v3f			normal;
}					t_ray_result;

typedef struct s_aabb_x2
{
	t_v3f			r_org[3];
	t_v3f			r_inv[3];
	t_v3f			b_min_x;
	t_v3f			b_max_x;
	t_v3f			b_min_y;
	t_v3f			b_max_y;
	t_v3f			b_min_z;
	t_v3f			b_max_z;
	t_v3f			t1;
	t_v3f			t2;
	t_v3f			tmin;
	t_v3f			tmax;
}					t_aabb_x2;

typedef struct s_bvh_context
{
	int				stack[64];
	int				stack_ptr;
	double			t;
	double			best_dist;
	int				best_index;
	int				node_idx;
	t_bvh_node		*node;
	int				l_idx;
	int				r_idx;
	float			dist[2];
	t_aabb_x2		aabb_c;
}					t_bvh_context;

typedef struct s_bvh_context_debug
{
	int				stack[64];
	int				stack_ptr;
	int				nodes_traversed;
	double			t;
	double			best_dist;
	int				best_index;
	t_bvh_node		*current;
}					t_bvh_context_debug;

typedef struct s_out_buffer
{
	t_v3f			hit_normal;
	t_v3f			hit_point;
}					t_out_buffer;

typedef struct s_thread_render_context
{
	t_v2i			pixel;
	t_ray			ray;
	t_v3f			target;
	t_out_buffer	out;
}					t_thread_render_context;

typedef struct s_get_light_context
{
	t_ray			light_ray;
	double			light_dist;
	double			dist;
	int				hit;
	t_v3f			color;
	t_v3f			new_color;
	double			plane_dist;
	int				rand_light;
	t_light			light;
}					t_get_light_context;

typedef struct s_get_emissive_light_context
{
	t_ray			light_ray;
	int				hit;
	int				rand_emissive;
	t_object		obj;
	char			bypass_normal;
	float			emission_dot;
	float			dist;
	int				raw_hit;
	float			emission_surface_coef;
	float			geom_term;
	float			weigh;
	t_v3f			max;
	t_v3f			targeted_light;
}					t_get_emissive_light_context;

typedef struct s_pixel_color_context
{
	int				hit;
	double			distance;
	t_v3f			out_color;
	t_v3f			hit_normal;
	t_v3f			hit_point;
	t_v2f			hit_uv;
	t_v3f			light_color;
	t_material		mat;
	double			do_reflect;
	t_v3f			reflected;
	t_v3f			new_dir;
	char			hit_side;

}					t_pixel_color_context;

typedef struct s_viewport_context
{
	t_camera		cam;
	float			aspect_ratio;
	float			theta;
	float			half_width;
	float			half_height;
	t_v3f			cam_right;
	t_v3f			cam_up;
	t_v3f			pixel_center_offset;
}					t_viewport_context;

#endif