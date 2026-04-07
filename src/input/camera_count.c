/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <tpotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:12:57 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/07 16:16:21 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_camera_count(t_data *d)
{
	if (ft_get_key_down(XK_minus, d))
	{
		remove_camera(d->scene);
		refresh_grid(d);
	}
	if (ft_get_key_down(XK_equal, d))
	{
		add_camera(d->scene, &d->scene->cameras[d->scene->active_camera]);
		refresh_grid(d);
	}
}
