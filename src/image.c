/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:33:35 by pberne            #+#    #+#             */
/*   Updated: 2026/01/31 12:37:14 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_create_image(t_data *d)
{
	t_image	image;

	image.ptr = mlx_new_image(d->mlx, WIDTH_WIN, HEIGHT_WIN);
	if (!image.ptr)
		ft_exit(MALLOC_FAILED);
	image.accumulated_addr = ft_malloc(sizeof(double) * WIDTH_WIN * HEIGHT_WIN
			* 3);
	ft_add_exit(d, ft_exit_destroy_image);
	image.addr = mlx_get_data_addr(image.ptr, &(image.bpp), &(image.line_size),
			&(image.endian));
	d->image = image;
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
