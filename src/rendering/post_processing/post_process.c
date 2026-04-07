/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:00:51 by pberne            #+#    #+#             */
/*   Updated: 2026/04/07 16:59:11 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	camera_outline(t_image *img, t_camera cam, int active)
{
	int		color;
	t_rect	r;
	int		i;

	color = 0x00424242;
	if (active)
		color = 0x0000FF00;
	r = cam.rect;
	i = 0;
	while (i < r.w)
	{
		ft_put_pxl(img->addr, (t_v2i){.x = i + r.x, .y = r.y}, color);
		ft_put_pxl(img->addr, (t_v2i){.x = i + r.x, .y = r.y + r.h - 1}, color);
		i++;
	}
	i = 1;
	while (i < r.h - 1)
	{
		ft_put_pxl(img->addr, (t_v2i){.x = r.x, .y = i + r.y}, color);
		ft_put_pxl(img->addr, (t_v2i){.x = r.x + r.w - 1, .y = i + r.y}, color);
		i++;
	}
}

void	ft_post_process(t_data *d)
{
	int		i;
	float	coef;
	t_v3f	max;

	i = 0;
	d->frame_count += 1.0f;
	coef = 1.0f / d->frame_count;
	max = (t_v3f){{1.0, 1.0, 1.0}};
	while (i < SCREEN_SIZE)
	{
		ft_put_pxl_addr((int *)d->image.addr, i,
			ft_v3f_to_int_color(ft_v3f_min(ft_v3f_scale(
						d->image.current_frame[i], coef), max)));
		i++;
	}
	i = 0;
	while (d->scene->num_cameras > 1 && i < d->scene->num_cameras)
	{
		camera_outline(&d->image, d->scene->cameras[i],
			i == d->scene->active_camera);
		i++;
	}
}
