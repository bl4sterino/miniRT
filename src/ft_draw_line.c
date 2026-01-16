/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:16:51 by pberne            #+#    #+#             */
/*   Updated: 2025/12/08 17:54:43 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_point(t_data *d, t_screenpoint start, t_screenpoint end)
{
	if (start.depth < 0)
		ft_put_pxl_d(&(d->image), (t_v2i){end.x, end.y},
			ft_rgb_to_int(end.color), end.depth);
	else if (end.depth < 0)
		ft_put_pxl_d(&(d->image), (t_v2i){start.x, start.y},
			ft_rgb_to_int(start.color), start.depth);
	else if (end.depth < start.depth)
		ft_put_pxl_d(&(d->image), (t_v2i){end.x, end.y},
			ft_rgb_to_int(end.color), end.depth);
	else
		ft_put_pxl_d(&(d->image), (t_v2i){start.x, start.y},
			ft_rgb_to_int(start.color), start.depth);
}

/*void	ft_draw_x_line(t_data *d, t_screenpoint start, t_screenpoint end,
		int size)
{
	float			progress;
	int				i;
	int				increment;
	t_v2i			pos;
	t_screenpoint	temp;
	float			depth;

	i = 0;
	increment = ft_sign(size);
	if (start.depth < 0)
	{
		temp = start;
		start = end;
		end = temp;
	}
	size = ft_abs(size);
	pos.x = start.x;
	while (pos.x != end.x)
	{
		progress = (float)i / (float)size;
		pos.y = ft_lerpi(start.y, end.y, progress);
		depth = ft_lerpf(start.depth, end.depth, progress);
		if (depth < 0)
			return ;
		ft_put_pxl_d(&(d->image), pos, ft_color_lerp_rgb_to_int(start.color,
				end.color, progress), depth);
		pos.x += increment;
		i++;
	}
	ft_put_pxl_d(&(d->image), (t_v2i){end.x, end.y}, ft_rgb_to_int(end.color),
		end.depth);
}

void	ft_draw_y_line(t_data *d, t_screenpoint start, t_screenpoint end,
		int size)
{
	float			progress;
	int				i;
	int				increment;
	t_v2i			pos;
	t_screenpoint	temp;
	float			depth;

	i = 0;
	increment = ft_sign(size);
	if (start.depth < 0)
	{
		temp = start;
		start = end;
		end = temp;
	}
	size = ft_abs(size);
	pos.y = start.y;
	while (pos.y != end.y)
	{
		progress = (float)i / (float)size;
		pos.x = ft_lerpi(start.x, end.x, progress);
		depth = ft_lerpf(start.depth, end.depth, progress);
		if (depth < 0)
			return ;
		ft_put_pxl_d(&(d->image), pos, ft_color_lerp_rgb_to_int(start.color,
				end.color, progress), depth);
		pos.y += increment;
		i++;
	}
	ft_put_pxl_d(&(d->image), (t_v2i){end.x, end.y}, ft_rgb_to_int(end.color),
		end.depth);
}

void	ft_swap_sp(t_screenpoint *a, t_screenpoint *b)
{
	t_screenpoint	c;

	c = *a;
	*a = *b;
	*b = c;
}*/

int	ft_check_if_valid(t_screenpoint *start, t_screenpoint *end)
{
	if (start->depth < 0.0f || end->depth < 0.0f)
		return (0);
	if (start->x < X_WIN_MIN || end->x < X_WIN_MIN)
		return (0);
	if (start->x >= X_WIN_MAX || end->x >= X_WIN_MAX)
		return (0);
	if (start->y < Y_WIN_MIN || end->y < Y_WIN_MIN)
		return (0);
	if (start->y >= Y_WIN_MAX || end->y >= Y_WIN_MAX)
		return (0);
	else
		return (1);
}

void	ft_draw_line(t_data *d, t_screenpoint start, t_screenpoint end)
{
	int			x_dist;
	int			y_dist;
	t_line_data	ld;

	if (!ft_check_if_valid(&start, &end))
		return ;
	x_dist = end.x - start.x;
	y_dist = end.y - start.y;
	if (x_dist == 0 && y_dist == 0)
		ft_draw_point(d, start, end);
	else if (ft_abs(x_dist) > ft_abs(y_dist))
	{
		ld = ft_init_line(start, end, ft_abs(x_dist));
		ft_bresenham_x(d, start, end, ld);
	}
	else
	{
		ld = ft_init_line(start, end, ft_abs(y_dist));
		ft_bresenham_y(d, start, end, ld);
	}
}
