/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:04:26 by pberne            #+#    #+#             */
/*   Updated: 2026/01/20 11:06:34 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H

# include "rt.h"

typedef struct s_rgb
{
	char			r;
	char			g;
	char			b;
}					t_rgb;

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
	float			cos_y;
	float			sin_y;
	float			cos_p;
	float			sin_p;
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

typedef struct t_data
{
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

#endif