/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:00:51 by pberne            #+#    #+#             */
/*   Updated: 2026/02/22 19:53:59 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


void	ft_get_averaged_frame(t_data *d)
{
	int		i;
	double	coef;

	d->frame_count += 1.0;
	coef = 1.0 / d->frame_count;
	i = 0;
	while (i < WIDTH_WIN * HEIGHT_WIN * 3)
	{
		d->image.averaged_colors[i] = fminf(1.0, (float)(d->image.accumulated_addr[i]
				* coef));
		i++;
	}
}

void	ft_post_process(t_data *d)
{
	int		i;
	t_v2i	pos;

	ft_get_averaged_frame(d);
	i = 0;
	pos.y = 0;
	while (pos.y < HEIGHT_WIN)
	{
		pos.x = 0;
		while (pos.x < WIDTH_WIN)
		{
			ft_put_pxl(d->image.addr, pos,
				ft_floats_to_int_color(d->image.averaged_colors[i],
					d->image.averaged_colors[i + 1], d->image.averaged_colors[i
					+ 2]));
			i += 3;
			pos.x++;
		}
		pos.y++;
	}
}
