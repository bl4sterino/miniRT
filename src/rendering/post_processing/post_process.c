/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:00:51 by pberne            #+#    #+#             */
/*   Updated: 2026/04/08 12:58:06 by pberne           ###   ########.fr       */
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

void	ft_average_frame_to_int_buffer(int *int_buffer, t_v3f *vec_buffer,
		t_camera *cam)
{
	int		y;
	int		x;
	float	coef;
	t_v3f	max;
	int		index;

	max = (t_v3f){{1.0, 1.0, 1.0}};
	coef = 1.0f / cam->frame_count;
	y = cam->rect.y;
	while (y < cam->rect.y + cam->rect.h)
	{
		x = cam->rect.x;
		while (x < cam->rect.x + cam->rect.w)
		{
			index = y * WIDTH_WIN + x;
			int_buffer[index] = ft_v3f_to_int_color(
					ft_v3f_min(ft_v3f_scale(vec_buffer[index], coef), max));
			x++;
		}
		y++;
	}
}

void	ft_post_process(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->scene->num_cameras)
	{
		d->scene->cameras[i].frame_count += 1.0f;
		ft_average_frame_to_int_buffer((int *)d->image.addr,
			d->image.current_frame, &d->scene->cameras[i]);
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
