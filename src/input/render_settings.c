/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:58:33 by pberne            #+#    #+#             */
/*   Updated: 2026/04/03 14:37:10 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_render_settings_2(t_data *d)
{
	if (ft_get_key_down(XK_n, d))
	{
		if (d->render_mode == RENDER_NORMALS)
			d->render_mode = RENDER_DEFAULT;
		else
			d->render_mode = RENDER_NORMALS;
		d->dirty_frame = 1;
	}
}

void	ft_render_settings(t_data *d)
{
	if (ft_get_key_down(XK_e, d))
	{
		if (d->render_mode == RENDER_BVH)
			d->render_mode = RENDER_DEFAULT;
		else
			d->render_mode = RENDER_BVH;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(XK_f, d))
	{
		d->target_ray_bounces = ft_max(0, d->target_ray_bounces
				- tn_i(ft_get_key(MOUSE_RIGHT, d), 10, 1));
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(XK_g, d))
	{
		d->target_ray_bounces += tn_i(ft_get_key(MOUSE_RIGHT, d), 10, 1);
		d->dirty_frame = 1;
	}
	ft_render_settings_2(d);
}
