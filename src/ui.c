/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:26:42 by pberne            #+#    #+#             */
/*   Updated: 2026/01/16 11:14:22 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_draw_double(t_data *d, t_draw_arg arg, char *prefix_arg, double nb)
{
	char	*nbstr;
	char	*fullstr;

	nbstr = ft_dtoa_p(nb, 2);
	if (!nbstr)
	{
		ft_exit(MALLOC_FAILED);
	}
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

void	ft_draw_int(t_data *d, t_draw_arg arg, char *prefix_arg, int nb)
{
	char	*nbstr;
	char	*fullstr;

	nbstr = ft_itoa(nb);
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

void	ft_draw_str(t_data *d, t_draw_arg arg, char *str)
{
	ft_draw_rectangle(d->image, arg.pos, arg.size, arg.background_color);
	mlx_string_put(d->mlx, d->window, arg.pos.x + 3, arg.pos.y + arg.size.y - 3,
		ft_rgb_to_int((t_rgb){255, 255, 255}), str);
}
