/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_floating.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:26:42 by pberne            #+#    #+#             */
/*   Updated: 2026/03/06 13:25:33 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_draw_double_8(t_data *d, t_draw_arg arg, char *prefix_arg, double nb)
{
	char	*nbstr;
	char	*fullstr;

	nbstr = ft_dtoa_p(nb, 8);
	if (!nbstr)
		ft_exit(MALLOC_FAILED);
	fullstr = ft_strjoin(prefix_arg, nbstr);
	if (!fullstr)
	{
		free(nbstr);
		ft_exit(MALLOC_FAILED);
	}
	ft_draw_rectangle(d->image, arg.pos, arg.size, arg.background_color);
	mlx_string_put(d->mlx, d->window, arg.pos.x + 3, arg.pos.y + arg.size.y - 3,
		ft_rgb_to_int((t_rgb){255, 255, 255}), fullstr);
	free(fullstr);
	free(nbstr);
}

void	ft_draw_float_8(t_data *d, t_draw_arg arg, char *prefix_arg, float nb)
{
	ft_draw_double_8(d, arg, prefix_arg, (double)nb);
}

void	ft_draw_double(t_data *d, t_draw_arg arg, char *prefix_arg, double nb)
{
	char	*nbstr;
	char	*fullstr;

	nbstr = ft_dtoa_p(nb, 1);
	if (!nbstr)
		ft_exit(MALLOC_FAILED);
	fullstr = ft_strjoin(prefix_arg, nbstr);
	if (!fullstr)
	{
		free(nbstr);
		ft_exit(MALLOC_FAILED);
	}
	ft_draw_rectangle(d->image, arg.pos, arg.size, arg.background_color);
	mlx_string_put(d->mlx, d->window, arg.pos.x + 3, arg.pos.y + arg.size.y - 3,
		ft_rgb_to_int((t_rgb){255, 255, 255}), fullstr);
	free(fullstr);
	free(nbstr);
}

void	ft_draw_float(t_data *d, t_draw_arg arg, char *prefix_arg, float nb)
{
	ft_draw_double(d, arg, prefix_arg, (double)nb);
}
