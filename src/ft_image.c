/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:33:35 by pberne            #+#    #+#             */
/*   Updated: 2025/12/06 19:52:31 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_create_image(t_data *d)
{
	t_image	image;

	image.ptr = mlx_new_image(d->mlx, WIDTH_WIN, HEIGHT_WIN);
	image.addr = mlx_get_data_addr(image.ptr, &(image.bpp), &(image.line_size),
			&(image.endian));
	d->image = image;
	d->image.depth_map = ft_malloc(sizeof(float) * WIDTH_WIN * HEIGHT_WIN);
}

void	ft_put_pxl_d(t_image *img, t_v2i pos, int color, float depth)
{
	char			*pixel;
	unsigned long	depth_offset;

	depth_offset = pos.y * WIDTH_WIN + pos.x;
	if (pos.x >= 0 && pos.x < WIDTH_WIN && pos.y >= 0 && pos.y < HEIGHT_WIN
		&& (depth == 0 || img->depth_map[depth_offset] > depth))
	{
		img->depth_map[depth_offset] = depth;
		pixel = img->addr + (pos.y * img->line_size + pos.x * IMAGE_BPP);
		*(int *)pixel = color;
	}
}

void	ft_put_pxl(t_image *img, t_v2i pos, int color)
{
	char	*pixel;

	if (pos.x >= 0 && pos.x < WIDTH_WIN && pos.y >= 0 && pos.y < HEIGHT_WIN)
	{
		pixel = img->addr + (pos.y * img->line_size + pos.x * IMAGE_BPP);
		*(int *)pixel = color;
	}
}

void	ft_draw_rectangle(t_image image, t_v2i pos, t_v2i size, t_rgb color)
{
	t_v2i	current_pos;
	int		rbg_color;

	current_pos.x = pos.x;
	current_pos.y = pos.y;
	rbg_color = ft_rgb_to_int(color);
	while (current_pos.y < pos.y + size.y)
	{
		current_pos.x = pos.x;
		while (current_pos.x < pos.x + size.x)
		{
			ft_put_pxl(&image, current_pos, rbg_color);
			current_pos.x++;
		}
		current_pos.y++;
	}
}
