/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:58:33 by pberne            #+#    #+#             */
/*   Updated: 2026/02/26 10:39:21 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_render_settings(t_data *d)
{
	if (ft_get_key_down(KEY_E, d))
	{
		if(d->render_mode == RENDER_BVH)
			d->render_mode = RENDER_DEFAULT;
		else
			d->render_mode = RENDER_BVH;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(KEY_F, d))
	{
		d->target_ray_bounces = ft_max(0, d->target_ray_bounces - 1);
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(KEY_G, d))
	{
		d->target_ray_bounces += 1;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(KEY_B, d))
	{
		d->denoise = !d->denoise;
		d->dirty_frame = 1;
	}
	if (ft_get_key_down(KEY_N, d))
	{
		if(d->render_mode == RENDER_NORMALS)
			d->render_mode = RENDER_DEFAULT;
		else
			d->render_mode = RENDER_NORMALS;
		d->dirty_frame = 1;
	}
}
