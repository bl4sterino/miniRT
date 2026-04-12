/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:33:35 by pberne            #+#    #+#             */
/*   Updated: 2026/04/12 15:44:24 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_setup_target_color_image(t_data *d)
{
	int	i;

	d->image.targets_colors = ft_malloc(sizeof(t_v3f) * 1024);
	i = 0;
	while (i < 1024)
	{
		d->image.targets_colors[i] = v3f(0.3f + 0.7f * fast_rand(), 0.3f + 0.7f
				* fast_rand(), 0.3f + 0.7f * fast_rand());
		i++;
	}
}

void	ft_create_image(t_data *d)
{
	t_image	image;

	image.ptr = mlx_new_image(d->mlx, WIDTH_WIN, HEIGHT_WIN);
	if (!image.ptr)
		ft_exit(MALLOC_FAILED);
	ft_add_exit(image.ptr, ft_exit_destroy_image);
	image.current_frame = ft_malloc(sizeof(t_v3f) * SCREEN_SIZE);
	image.normals = ft_malloc(sizeof(t_v3f) * SCREEN_SIZE);
	image.ray_targets = ft_malloc(sizeof(int) * SCREEN_SIZE);
	ft_memset_int(image.ray_targets, SELECTED_NONE, SCREEN_SIZE);
	ft_bzero(image.normals, sizeof(t_v3f) * SCREEN_SIZE);
	image.addr = mlx_get_data_addr(image.ptr, &(image.bpp), &(image.line_size),
			&(image.endian));
	d->image = image;
	ft_setup_target_color_image(d);
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
			ft_put_pxl(image.addr, current_pos, rbg_color);
			current_pos.x++;
		}
		current_pos.y++;
	}
}
