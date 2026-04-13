/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:12:57 by tpotier           #+#    #+#             */
/*   Updated: 2026/04/13 16:26:29 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_camera_count(t_data *d)
{
	if (ft_get_key_down(XK_minus, d))
	{
		pthread_mutex_lock(&d->threads_data.task_mutex);
		remove_camera(d->scene);
		pthread_mutex_unlock(&d->threads_data.task_mutex);
		refresh_grid(d);
	}
	if (ft_get_key_down(XK_equal, d))
	{
		pthread_mutex_lock(&d->threads_data.task_mutex);
		add_camera(d->scene, &d->scene->cameras[d->scene->active_camera]);
		pthread_mutex_unlock(&d->threads_data.task_mutex);
		refresh_grid(d);
	}
}
