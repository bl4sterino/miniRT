/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:58:33 by pberne            #+#    #+#             */
/*   Updated: 2026/03/28 14:44:37 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_render_settings_2(t_data *d)
{
	if (ft_get_key_down(KEY_N, d))
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
	if (ft_get_key_down(KEY_E, d))
	{
		if (d->render_mode == RENDER_BVH)
			d->render_mode = RENDER_DEFAULT;
		else
			d->render_mode = RENDER_BVH;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(KEY_F, d))
	{
		d->target_ray_bounces = ft_max(0, d->target_ray_bounces
				- tn_i(ft_get_key(MOUSE_RIGHT, d), 10, 1));
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(KEY_G, d))
	{
		d->target_ray_bounces += tn_i(ft_get_key(MOUSE_RIGHT, d), 10, 1);
		d->dirty_frame = 1;
	}
	ft_render_settings_2(d);
}
