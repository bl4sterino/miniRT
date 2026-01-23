/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:04:26 by pberne            #+#    #+#             */
/*   Updated: 2026/01/23 07:50:25 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H

# include "rt.h"

enum				e_dimensions
{
	WIDTH_WIN = 1280,
	HEIGHT_WIN = 720,
	LINE_SIZE = WIDTH_WIN * 4,
	SCREEN_SIZE = WIDTH_WIN * HEIGHT_WIN
};

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

typedef struct t_data
{
	void			*mlx;
	void			*window;
	t_image			image;
	t_input			input;
	double			deltatime;
	struct timeval	last_tv;
	char			*fpsstr;
	unsigned long	frame_count;
	t_scene			*scene;
}					t_data;

typedef struct s_ray
{
	t_v3d			origin;
	t_v3d			direction;
}					t_ray;

#endif